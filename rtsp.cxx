#include <fcntl.h>

#include "config.h"
#include "common.h"


#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "WAVAudioFileServerMediaSubsession.h"

UsageEnvironment* env;

Boolean reuseFirstSource = True;

Boolean iFramesOnly = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
                           char const* streamName, char const* inputFileName); // fwd

extern "C" void* min1(void *) {
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = NULL;

	RTSPServer* rtspServer = RTSPServer::createNew(*env, RTSP_PORT, authDB);
	if (rtspServer == NULL) {
		*env << "[liveMedia] Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}

	char const* descriptionString	= "Session streamed by " PACKAGE " (" PACKAGE_URL ")";

	
	char const* streamName = "";

	int fd = open(MODE_RTSP_FIFO_FILE, O_RDONLY); // open inmediatelly to avoid hanging write process
	close(fd);
	char const* inputFileName = MODE_RTSP_FIFO_FILE;
	char const* inputFileName2;
	if(RUN_AUDIO) { 
		int fd2 = open(MODE_RTSP_FIFO_FILE2, O_RDONLY); // open inmediatelly to avoid hanging write process
		close(fd2);
		inputFileName2 = MODE_RTSP_FIFO_FILE2;
		}
		
	OutPacketBuffer::maxSize = 100000;
	ServerMediaSession* sms
		= ServerMediaSession::createNew(*env, streamName, streamName, descriptionString);
	*env << "[liveMedia] Add MPEG4VideoFileServerMediaSubsession on fifo pipe: " << inputFileName << "\n";
	sms->addSubsession(MPEG4VideoFileServerMediaSubsession::createNew(*env, inputFileName, reuseFirstSource));
	if(RUN_AUDIO) { 
		*env << "[liveMedia] Add WAVAudioFileServerMediaSubsession1 on fifo pipe: " << inputFileName2 << "\n";
		sms->addSubsession(WAVAudioFileServerMediaSubsession1::createNew(*env, inputFileName2, reuseFirstSource));
	}
	rtspServer->addServerMediaSession(sms);

	announceStream(rtspServer, sms, streamName, inputFileName);

	env->taskScheduler().doEventLoop();
}

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
                           char const* streamName, char const* inputFileName) {
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env << "[liveMedia] Starting RTSP server on \"" << url << "\"\n";
	delete[] url;
}


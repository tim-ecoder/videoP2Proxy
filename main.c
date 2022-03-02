/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * Copyright (C) 2018 Miguel Angel Nubla <miguelangel.nubla@gmail.com>
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "config.h"
#include "common.h"
#include "client.h"
#include "rtsp.h"

void print_usage() {
    printf(
    		"Usage: videop2proxy --cam-id LAYDLWRCR5U953N9111A --cam-login admin -cam-pass 1111111111 [...] \n"
    		"\n"
    		"Options:\n"
    		"  --cam-id CAMERA-P2P-UID		[Required] Camera UID address (Like: LAYDLWRCR5U953N9111A). Written on camera.\n"
    		"  --cam-login CAMERA-P2P-LOGIN		[Required] Camera p2p login. (SEP-500: \"admin\" hardcoded on camera)\n"
            "  --cam-pass CAMERA-P2P-PASSWORD	[Required] Camera p2p password. (SEP-500: \"000000\" default if not changed)\n"
			"  --rtsp-port RTSP-PORT         	[OPTIONAL] RTSP server port. If not set DEFAULT: 554\n"
    );
}

int main(int argc, char *argv[]) {
	


   static struct option long_options[] = {
        {"cam-id",      required_argument, 0,  'i' },
        {"cam-login",   required_argument, 0,  'l' },
		{"cam-pass",    required_argument, 0,  'p' },
		{"rtsp-port",   optional_argument, 0,  'r' },
        {0,        0,                 0,  0   }
    };

	char* cam_id = "";
	char* cam_login = "";
	char* cam_pass = "";
	int rtsp_port = 0;


	
	int opt = 0;
    int long_index = 0;
	char optc = 0;
	
    while ((opt = getopt_long(argc, argv,"i:l:p:r::", long_options, &long_index )) != -1) 
	{
		optc = (char)opt;
		
        switch (optc) {
             case 'i' : 
				cam_id = optarg;
                break;
             case 'l' : 
				cam_login = optarg;
                break;
             case 'p' : 
				cam_pass = optarg;
                break;
             case 'r' : 
				rtsp_port = atoi(optarg);
                break;
             default: 
				print_usage();
                return 0;
        }
    }

	char template[] = "/tmp/videop2proxy_v.XXXXXX";
	char* tmpDir = mkdtemp(template);
	char* tmpFile = "/fifo";

	MODE_RTSP_FIFO_FILE = malloc(strlen(tmpDir) + strlen(tmpFile) + 1);
	strcat(MODE_RTSP_FIFO_FILE, tmpDir);
	strcat(MODE_RTSP_FIFO_FILE, tmpFile);

	mkfifo(MODE_RTSP_FIFO_FILE, 0600);


	char template2[] = "/tmp/videop2proxy_a.XXXXXX";
	char* tmpDir2 = mkdtemp(template2);
	char* tmpFile2 = "/fifo";

	MODE_RTSP_FIFO_FILE2 = malloc(strlen(tmpDir2) + strlen(tmpFile2) + 1);
	strcat(MODE_RTSP_FIFO_FILE2, tmpDir2);
	strcat(MODE_RTSP_FIFO_FILE2, tmpFile2);

	mkfifo(MODE_RTSP_FIFO_FILE2, 0600);

	
	pthread_t ThreadRTSP = 0;
	int ret;
	if ((ret=pthread_create(&ThreadRTSP, NULL, &min1, NULL)))
	{
		DPRINTF("Create RTSP thread failed\n");
		return 1;
	}


	MODE_RTSP_FIFO = open(MODE_RTSP_FIFO_FILE, O_WRONLY);
	MODE_RTSP_FIFO2 = open(MODE_RTSP_FIFO_FILE2, O_WRONLY);


	DPRINTF("Starting liveMedia server as proxy...\n");
	int delay = 10;
    while (1)
	{
		//clientRun("LAYDLWRCR5U953N9111A", "admin", "111111");
		clientRun(cam_id, cam_login, cam_pass);
		DPRINTF("Error, waiting %d seconds and trying again.\n", delay);
		sleep(delay);
	}
}


#include <stdio.h>

#include "common.h"
#include "av.h"
#include "iotc.h"

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
#include "rtsp.h"

int clientRun(char* p2p_id, char* userName, char* passWord)
{
	int avIndex = 0;
	int sid = 0;
    if (enterIOTC(&avIndex, p2p_id, userName, passWord, &sid) && startIOTC(&avIndex)) {
        DPRINTF("[P2P client] running...\n");
		startReceive(&avIndex);		
		stopIOTC(&avIndex);
		quitIOTC(&avIndex, &sid);
		DPRINTF("[P2P client] stopped.\n");
        return 1;
    } else {
        DPRINTF("[P2P client] starting or connection error.\n");
		return 1;
    }
}


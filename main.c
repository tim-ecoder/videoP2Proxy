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


int main(int argc, char *argv[]) {


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
		clientRun("LAYDLWRCR5U953N9111A", "admin", "111111");
		DPRINTF("Error, waiting %d seconds and trying again.\n", delay);
		sleep(delay);
	}
}


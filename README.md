# videoP2Proxy
Proxy to enable Samsung SEP-5002RDP (HANWHA TECHWIN) WISENET P2P (AVAPIs, IOTCAPIs) only cameras to work with RTSP protocol.
**Works without changing the firmware of the camera, original LCD-screen continue to work.**

*** TESTED ONLY Samsung SEP-5002RDP BABY CAMERA ***

**** SOUND IS NOW IMPLEMENTED (Original miguelangel.nubla did not implemet sound) ****

**** SOUND SETTINGS HARDCODED: PCM, 1ch, 8bit, 16000Hz****

**** LINUX ONLY ****

*** 4DEV-s: DEVELOPED WITH ANJUTA ***

 Known working models
-----------
* Samsung SEP-5002RDP

 Known BUG-s
-----------
* Synology Surveillance does not recognize sound settings from liveMedia sink (try to rtsp-proxy and re-encode with ffmpeg (ffserver))

Quick start on Ubuntu
-----------

#### Install dependencies
1. Install dependency packages
```
sudo apt-get install build-essential git autoconf automake libtool liblivemedia-dev libjson-c-dev
```
##### Clone repository
```
git clone https://github.com/tim-ecoder/videoP2Proxy.git
cd videoP2Proxy
```

##### Build
```
./autogen.sh
make
sudo make install
```

##### Run the RTSP proxy 
```
sudo videop2proxy --cam-id LAYDLWRCR5U953N9111A --cam-login admin --cam-pass 111111
```
Other commandline arguments [optional] --rtsp-port 555 [optional] --audio-enable 0

Example output running correctly:
```
Starting P2P-camera to RTSP proxy-server
[P2P] Client starting
[P2P] IOTC_Initialize2...
[liveMedia] Add MPEG4VideoFileServerMediaSubsession on fifo pipe: /tmp/videop2proxy_v.853yuV/fifo
[liveMedia] Add WAVAudioFileServerMediaSubsession1 on fifo pipe: /tmp/videop2proxy_a.czo5oY/fifo
[liveMedia] Starting RTSP server on "rtsp://172.17.20.66/"
[P2P] IOTC_Connect_ByUID_Parallel... SID:0
[P2P] avClientStart2 UID: LAYDLWRCR5U953N9111A userName: admin passWord: 111111
[P2P] avClientStart2 mAvIndex=0
[P2P] startIOTC video ret=0
[P2P] startIOTC audio ret=0
[P2P] Client running...
[P2P][ReceiveVideo] Write to fifo pipe: 3
[P2P][ReceiveAudio] Write to fifo pipe: 6
[P2P][ReceiveAudio] Running...
[P2P][ReceiveVideo] Running...

```


Original made by and thanks
-----------

Was this useful to you? Consider donating  
@PayPal: miguelangel.nubla@gmail.com  
@bitcoin: bc1q2s5jdm7vem8ygv2fgxtfukmxuruyfsqjrexk3c

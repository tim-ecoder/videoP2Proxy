# videoP2Proxy
Proxy to enable Samsung SEP-5002RDP (HANWHA TECHWIN) WISENET P2P (AVAPIs, IOTCAPIs) only cameras to work with RTSP protocol.
**Works without changing the firmware of the camera, original LCD-screen continue to work.**

*** TESTED ONLY Samsung SEP-5002RDP ***
*** FOR DEVELOPERS ONLY ***
*** BUILD WITH ANJUTA ***

**** SOUND IMPLEMENTED ****
**** SOUND SETTINGS HARDCODED: PCM, 1ch, 8bit, 16000Hz****
**** LINUX ONLY ****

!!!! NOT STABLE !!!!

 Known working models
-----------
* Samsung SEP-5002RDP

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

##### Run the RTSP proxy +[optional] --rtsp-port 555
```
sudo videop2proxy --cam-id LAYDLWRCR5U953N9111A --cam-login admin --cam-pass 111111
```
Example output running correctly:
```
Starting proxy...
Starting RTSP server on "rtsp://192.168.1.2:554/"

[P2P client] starting...
IOTC_Initialize2...
IOTC_Connect_ByUID_Parallel... SID:0
avClientStart2... userName: c8da138df16 passWord: a1c8da1df11a
avClientStart2 mAvIndex=0
startIOTC video ret=0
startIOTC audio ret=0
[P2P client] running
[ReceiveVideo] Running
[ReceiveAudio] Running
```


Original made by and thanks
-----------

Was this useful to you? Consider donating  
@PayPal: miguelangel.nubla@gmail.com  
@bitcoin: bc1q2s5jdm7vem8ygv2fgxtfukmxuruyfsqjrexk3c

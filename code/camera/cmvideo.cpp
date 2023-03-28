#include "cmvideo.h"
#include <iostream>
 
CVVideo::CVVideo(QObject *parent):
    QThread(parent),
    dev(new cv::VideoCapture(0,cv::CAP_DSHOW)){
}
CVVideo::~CVVideo(){
    dev->release();
    delete dev;
    
}
void CVVideo::run(){
    while (true){
        cv::Mat  img;
        dev->read(img);
        emit sig_video(img);
        QThread:: usleep(100000);
    } 
}

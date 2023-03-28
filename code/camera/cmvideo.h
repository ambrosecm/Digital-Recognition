#ifndef CV_VIDEO_H
#define CV_VIDEO_H
#include <QtCore/QThread>
#include <opencv2/opencv.hpp>

class CVVideo : public QThread{
    Q_OBJECT
public:
    CVVideo(QObject *parent=0);
    ~CVVideo();
protected:
    virtual void run();
private:
    cv::VideoCapture  *dev;
signals:
    void sig_video(cv::Mat img);    
};

#endif


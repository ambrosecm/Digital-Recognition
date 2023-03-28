#ifndef CV_DIALOG_H
#define CV_DIALOG_H
#include <QtWidgets/QDialog>
#include "ui_video.h"
#include "cmvideo.h"

class CVDialog : public QDialog{
    Q_OBJECT
public:
    CVDialog(QWidget *parent=0);
    ~CVDialog();

private:
    Ui::video *ui;
    CVVideo *video; 
public slots:
    void save();
    void show_video(cv::Mat);
    void test();
    void exit();
};
#endif

#include <QtWidgets/QApplication>
#include "cmdialog.h"
#include <QtCore/QMetaType>
#include <opencv2/opencv.hpp>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <opencv2/opencv.hpp>

Q_DECLARE_METATYPE(cv::Mat);

int main(int argc, char **argv){
    QApplication app( argc, argv);
    qRegisterMetaType<cv::Mat>("Mat");
    qRegisterMetaType<cv::Mat>("Mat&");
    CVDialog dlg;
    dlg.show();
    return app.exec();
}
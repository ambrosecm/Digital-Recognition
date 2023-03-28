/********************************************************************************
** Form generated from reading UI file 'video.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_H
#define UI_VIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_video
{
public:
    QPushButton *btn_save;
    QLabel *lbl_video;
    QLabel *photo;
    QLabel *digit;
    QPushButton *test;
    QLabel *label;
    QPushButton *btn_exit;

    void setupUi(QDialog *video)
    {
        if (video->objectName().isEmpty())
            video->setObjectName(QString::fromUtf8("video"));
        video->resize(746, 470);
        btn_save = new QPushButton(video);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setGeometry(QRect(570, 160, 93, 28));
        lbl_video = new QLabel(video);
        lbl_video->setObjectName(QString::fromUtf8("lbl_video"));
        lbl_video->setGeometry(QRect(30, 50, 481, 361));
        photo = new QLabel(video);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(530, 20, 171, 121));
        digit = new QLabel(video);
        digit->setObjectName(QString::fromUtf8("digit"));
        digit->setGeometry(QRect(550, 250, 151, 61));
        digit->setAlignment(Qt::AlignCenter);
        test = new QPushButton(video);
        test->setObjectName(QString::fromUtf8("test"));
        test->setGeometry(QRect(570, 340, 93, 28));
        label = new QLabel(video);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(560, 210, 101, 31));
        btn_exit = new QPushButton(video);
        btn_exit->setObjectName(QString::fromUtf8("btn_exit"));
        btn_exit->setGeometry(QRect(630, 420, 91, 31));

        retranslateUi(video);
        QObject::connect(btn_save, SIGNAL(clicked()), video, SLOT(save()));
        QObject::connect(test, SIGNAL(clicked()), video, SLOT(test()));
        QObject::connect(btn_exit, SIGNAL(clicked()), video, SLOT(exit()));

        QMetaObject::connectSlotsByName(video);
    } // setupUi

    void retranslateUi(QDialog *video)
    {
        video->setWindowTitle(QCoreApplication::translate("video", "\350\247\206\351\242\221\347\233\221\346\216\247", nullptr));
        btn_save->setText(QCoreApplication::translate("video", "save", nullptr));
        lbl_video->setText(QString());
        photo->setText(QString());
        digit->setText(QString());
        test->setText(QCoreApplication::translate("video", "test", nullptr));
        label->setText(QCoreApplication::translate("video", "\350\257\206\345\210\253\347\232\204\346\225\260\345\255\227\346\230\257\357\274\232", nullptr));
        btn_exit->setText(QCoreApplication::translate("video", "exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class video: public Ui_video {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_H

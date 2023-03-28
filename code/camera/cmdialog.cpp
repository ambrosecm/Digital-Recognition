#include <opencv2/opencv.hpp>
#include <torch/torch.h>
#include "clenet.h"
#include "cmdialog.h"
#include "ui_video.h"


CVDialog::CVDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::video()),
    video(new CVVideo())
{
    ui->setupUi(this);
    QObject::connect(video, SIGNAL(sig_video(cv::Mat)), this, SLOT(show_video(cv::Mat)));
    video->start();
}
CVDialog::~CVDialog()
{
    delete ui;
    delete video;  
}
void CVDialog::save()
{
    QPixmap piximg = this->grab(QRect(40, 60, 460, 300));
    piximg.save("digit.png");
    cv::Mat c_img =cv::imread("digit.png");
    QImage qt_img(c_img.data,c_img.cols,c_img.rows, QImage::Format_RGB888);
    QPixmap qt_pixmap = QPixmap::fromImage(qt_img);
    ui->photo->setPixmap(qt_pixmap);
    ui->photo->setScaledContents(true);
}

void CVDialog::test()
{
    const char *data_filename = ".\\data";
    // 加载模型
    std::shared_ptr<Lenet5> model = std::make_shared<Lenet5>();
    torch::load(model, "model.pt");
    cv::Mat im = cv::imread("digit.png");
    cv::resize(im, im, cv::Size(28,28));
    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);   
    for(int y = 0; y <im.rows; y++)
    {
        uchar* row = im.ptr<uchar>(y);
        for(int x = 0;x < im.cols ; x++)
        {
            if(row[x]<150){
                row[x]=0;
            }
        }
    }

    im.convertTo(im, CV_32FC1, 1.0f / 255.0f);
    torch::Tensor  t_img = torch::from_blob(im.data, {1, 28, 28});
    t_img = t_img.view({-1, 1, 28, 28});
    torch::Tensor  y_ = model->forward(t_img);
    int32_t pred = y_.argmax(1).item<int32_t>();
    ui->digit->setText(QString::number(pred));
    QFont ft;
    ft.setPointSize(20);
    ui->digit->setFont(ft);
}
void CVDialog::exit()
{
    this->close();
}
void CVDialog::show_video(cv::Mat img)
{     
    cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
    QImage i_out(img.data, img.cols, img.rows, QImage::Format_RGB888);
    QPixmap p_out = QPixmap::fromImage(i_out); 
    ui->lbl_video->setPixmap(p_out);
    ui->lbl_video->setScaledContents(true);   
}
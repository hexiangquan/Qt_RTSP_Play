#include "frmmain.h"
#include "ui_frmmain.h"
#include <QDebug>
#include <QDir>

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);    

//    tempWidth = VIDEO_DEST_W;
//    tempHeight = VIDEO_DEST_H;
//    setFixedSize(tempWidth,tempHeight);

    QDir dir("D:/video");
    if ( !dir.exists() )
    {
        QDir dir2;
        bool ret = dir2.mkdir("D:/video");
        qDebug("mkdir the video directory:%d", ret);
    }

    InitFFmpg();

    connect( &timer, SIGNAL(timeout()),
             this, SLOT(slotVideoStart()) );
    timer.start(5000);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::slotSaveVideo(bool enable)
{
    if ( ffmpeg != NULL )
    {
        ffmpeg->SetSaveFile(enable);
    }
}

void frmMain::InitFFmpg()
{
//    char *temp1 = "rtsp://192.168.110.190:8554/1";
//    char *temp2 = "rtsp://192.168.1.11:8554/2";
    char *temp1 = "rtsp://192.168.1.30:554/udpstream_ch2";
    char *temp2 = "rtsp://192.168.1.30:554/udpstream_ch4";

    memset(url1, 0x0, sizeof(url1));
    memcpy(url1, temp1, strlen(temp1));
    memset(url2, 0x0, sizeof(url1));
    memcpy(url2, temp2, strlen(temp2));

    ffmpeg = new QFFmpeg(this);
    connect( ffmpeg, SIGNAL(GetImage(QImage)),
             this, SLOT(slotSetImage(QImage)) );
    connect( ffmpeg, SIGNAL(sigSaveFile()),
             this, SLOT(slotCheckVideoFile()) );
    ffmpeg->SetRtspUrl(url1, strlen(url1));

    rtsp = new RtspThread(this);
    rtsp->setffmpeg(ffmpeg);
}

void frmMain::slotSetImage(const QImage &image)
{
    if ( image.height() > 0 )
    {
        QPixmap pix = QPixmap::fromImage(image);
        ui->labVideo1->setPixmap(pix);
    }
}

void frmMain::slotVideoStart()
{
    if ( !ffmpeg->IsOpen() )
    {
        if ( ffmpeg->OpenVideoStream() )
        {
            rtsp->start();
            qDebug("Open Video Stream Success");
        }
        else
        {
            qDebug("Open Video Stream Error");
        }
    }
}

//循环存储视频文件
void frmMain::slotCheckVideoFile()
{
    QDir dir = QDir("D:/video", "*.mp4", QDir::Time| QDir::Reversed, QDir::Files);
    dir.setFilter(QDir::Files );
    dir.setSorting(QDir::Time | QDir::Reversed);
    unsigned int sizeMB = 0;
    unsigned int size = 0;
    int j = 0;

    QFileInfoList list = dir.entryInfoList();
    int fileCount = list.size();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        size = fileInfo.size();
        sizeMB += size>>20;
        qDebug() << QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName());
    }
    qDebug()<<"before delete: "<<sizeMB<<" file count: "<<fileCount;
    while ( fileCount > 5 || sizeMB > 200 )
    {
        QFileInfo removeFile = list.at(j);
        fileCount--;
        size = removeFile.size();
        sizeMB -= size>>20;

        dir.remove(removeFile.fileName());
        j++;

        qDebug()<<removeFile.fileName();
    }

    qDebug()<<"before delete: "<<sizeMB<<" file count: "<<fileCount;

}



#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QTimer>
#include "qffmpeg.h"
#include "rtspthread.h"

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

public slots:
    void slotSaveVideo(bool enable);
    void slotSetImage(const QImage &image);
private slots:
    void slotVideoStart();
    void slotCheckVideoFile();

private:
    Ui::frmMain *ui;

    char url1[128];
    char url2[128];
    int tempWidth;
    int tempHeight;
    QTimer timer;
    QFFmpeg *ffmpeg;
    RtspThread *rtsp;
    void InitFFmpg();
};
#endif // FRMMAIN_H

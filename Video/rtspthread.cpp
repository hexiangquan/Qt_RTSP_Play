#include "rtspthread.h"
#include <QDebug>
RtspThread::RtspThread(QObject *parent) :
    QThread(parent)
{
    ffmpeg = NULL;
}

void  RtspThread::run()
{
    if ( ffmpeg->IsOpen() )
        ffmpeg->Play();
}

void RtspThread::setffmpeg(QFFmpeg *f)
{
    ffmpeg = f;
}

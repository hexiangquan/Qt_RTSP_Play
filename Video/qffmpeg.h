#ifndef QFFMPEG_H
#define QFFMPEG_H

//必须加以下内否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

//引入ffmpeg头文
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libavutil/dict.h>
}

#include <QObject>
#include <QMutex>
#include <QImage>

//显示视频参数
#define VIDEO_DEST_W 900
#define VIDEO_DEST_H 685

class QFFmpeg : public QObject
{
    Q_OBJECT
public:
    explicit QFFmpeg(QObject *parent = 0);
    ~QFFmpeg();

    bool Init();
    bool OpenVideoStream();
    void CloseVideoStream();
    void Play();
    bool IsOpen();
    bool SetRtspUrl(const char *url, int len);
    void SetSaveFile(bool enable);
    void SaveVideoData(AVPacket *packet);
private:
    AVCodec *pAVCodec;
    QMutex mutex;
    AVPicture  pAVPicture;
    AVFormatContext *pAVFormatContext;
    AVFormatContext *fAVFormatContext;
    AVCodecContext *pAVCodecContext;
    AVCodecContext *fAVCodecContext;
    AVFrame *pAVFrame;
    SwsContext * pSwsContext;
    AVPacket pAVPacket;
    AVStream *out_stream;
    AVStream *in_stream;

    AVCodecContext *pAVEnCodecCtx;
    AVCodec *pAVEnCodec;

    int videoWidth;
    int videoHeight;
    int videoStreamIndex;

    bool flagOpen;
    bool flagSave;
    char rtspUrl[128];
signals:
    void GetImage(const QImage &image);
    void sigSaveFile();
public slots:

};

#endif // QFFMPEG_H

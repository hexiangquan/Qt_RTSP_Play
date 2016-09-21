#include "qffmpeg.h"
#include <QDateTime>
#include <QDebug>
#include "Common.h"

int vtime = 10 * 250;    //250 = 1000 * 2.5
static int packetCnt;

QFFmpeg::QFFmpeg(QObject *parent) :
    QObject(parent)
{
    //注册库中所有可用的文件格式和解码器
    av_register_all();
    //初始化网络流格式,使用RTSP网络流时必须先执行
    avformat_network_init();

    videoStreamIndex = -1;
    memset( rtspUrl, 0x0, sizeof(rtspUrl) );
    flagOpen = false;
    flagSave = true;
}

QFFmpeg::~QFFmpeg()
{
    qDebug("release qffmpeg, packetcnt:%d", packetCnt);
    if ( packetCnt > 0 )
    {
        //写入视频尾
        av_write_trailer(fAVFormatContext);
        avcodec_close(fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]);
        avio_close(fAVFormatContext->pb);
        av_free(fAVFormatContext);
        packetCnt = 0;
    }
}

bool QFFmpeg::OpenVideoStream()
{
    //申请一个AVFormatContext结构的内存,并进行简单初始化
    pAVFormatContext = avformat_alloc_context();
    pAVFrame = av_frame_alloc();

    AVDictionary *opts = NULL;
    av_dict_set( &opts, "stimeout", "6000", 0);
    //打开视频流
    int result = avformat_open_input(&pAVFormatContext, rtspUrl, NULL, &opts);
    if ( result < 0 )
    {
        avformat_free_context(pAVFormatContext);
        av_frame_free(&pAVFrame);
        qDebug()<<"open video input error";
        return false;
    }
    av_dict_free(&opts);
    //获取视频流信息
    result = avformat_find_stream_info(pAVFormatContext,NULL);
    if ( result < 0 )
    {
        qDebug()<<"find stream info error";
        return false;
    }

    videoStreamIndex = -1;
    //获取视频流索引
    for ( uint i = 0; i < pAVFormatContext->nb_streams; i++ )
    {
        if ( pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO )
        {
            videoStreamIndex = i;
            in_stream = pAVFormatContext->streams[i];
            break;
        }
    }

    if (videoStreamIndex ==-1)
    {
        qDebug()<<"get stream index error";
        return false;
    }

    //获取视频流的分辨率大小
    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    videoWidth = pAVCodecContext->width;
    videoHeight = pAVCodecContext->height;
    avpicture_alloc(&pAVPicture,AV_PIX_FMT_RGB24,VIDEO_DEST_W,VIDEO_DEST_H);

    //获取视频流解码器
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    pSwsContext = sws_getContext(videoWidth,videoHeight,AV_PIX_FMT_YUV420P,
                                 VIDEO_DEST_W,VIDEO_DEST_H,AV_PIX_FMT_RGB24,
                                 0,0,0,0);

    //打开对应解码器
    result = avcodec_open2(pAVCodecContext,pAVCodec,NULL);
    if ( result < 0 )
    {
        qDebug()<<"open av codec error";
        return false;
    }
    qDebug()<<"int stream success";

    flagOpen = true;
    return flagOpen;
}

void QFFmpeg::CloseVideoStream()
{
    avformat_free_context(pAVFormatContext);
    av_frame_free(&pAVFrame);
    sws_freeContext(pSwsContext);
    flagOpen = false;
}

void QFFmpeg::Play()
{
    int frameFinished = 0;

    while (true)
    {
        frameFinished = 0;

        av_init_packet(&pAVPacket);
        pAVPacket.size = 0;
        pAVPacket.data = NULL;

        if ( av_read_frame(pAVFormatContext, &pAVPacket) >= 0 )
        {
            if( pAVPacket.stream_index == videoStreamIndex )
            {
                avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                if ( frameFinished )
                {
                    mutex.lock();

                    sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data, pAVFrame->linesize,
                              0, videoHeight, pAVPicture.data, pAVPicture.linesize);

                    //发送获取一帧图像信号
                    QImage image(pAVPicture.data[0], VIDEO_DEST_W,VIDEO_DEST_H, QImage::Format_RGB888);
                    emit GetImage(image);

                    SaveVideoData(&pAVPacket);

                    mutex.unlock();
                }
            }
        }
        av_free_packet(&pAVPacket);//释放资源,否则内存会一直上升
    }
}

bool QFFmpeg::IsOpen()
{
    return flagOpen;
}

bool QFFmpeg::SetRtspUrl(const char *url, int len)
{
    memset( rtspUrl, 0x0, sizeof(rtspUrl) );

    if ( len > sizeof(rtspUrl) )
        return false;

    memcpy( rtspUrl, url, len );
    qDebug()<<"Set rtsp : "<<rtspUrl;
    return true;
}

void QFFmpeg::SetSaveFile(bool enable)
{
    flagSave = enable;
    if ( packetCnt > 0 )
    {
        //写入视频尾
        av_write_trailer(fAVFormatContext);
        avcodec_close(fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]);
        avio_close(fAVFormatContext->pb);
        av_free(fAVFormatContext);
        packetCnt = 0;
    }
}

void QFFmpeg::SaveVideoData(AVPacket *packet)
{
    char filename[64];

    if ( (!flagSave) || (packet == NULL) )
        return;

    if ( packetCnt == 0 )   //新建一个视频文件
    {
        emit sigSaveFile();
        QString tmp = "D:/video/" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".mp4";
        const char * tmp1 = tmp.toLatin1().data();
        strcpy(filename,tmp1);
        avformat_alloc_output_context2(&fAVFormatContext, NULL, NULL, filename);

        //根据网络流信息初始化输出流信息
        out_stream = avformat_new_stream(fAVFormatContext, NULL);
        {
            fAVCodecContext = out_stream->codec;
            fAVCodecContext->bit_rate = 400000;
            fAVCodecContext->codec_id = in_stream->codec->codec_id;
            fAVCodecContext->codec_type = in_stream->codec->codec_type;
            fAVCodecContext->time_base.num = in_stream->time_base.num;
            fAVCodecContext->time_base.den = in_stream->time_base.den;
            fAVCodecContext->width = in_stream->codec->width;
            fAVCodecContext->height = in_stream->codec->height;
            fAVCodecContext->pix_fmt = in_stream->codec->pix_fmt;
            fAVCodecContext->flags = in_stream->codec->flags;
            fAVCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;
            fAVCodecContext->me_range = in_stream->codec->me_range;
            fAVCodecContext->max_qdiff = in_stream->codec->max_qdiff;
            fAVCodecContext->qmin = in_stream->codec->qmin;
            fAVCodecContext->qmax = in_stream->codec->qmax;
            fAVCodecContext->qcompress = in_stream->codec->qcompress;
        }

        //打开输出文件
        avio_open(&fAVFormatContext->pb, filename, AVIO_FLAG_WRITE);

        //写文件头
        avformat_write_header(fAVFormatContext, NULL);
    }

    //保存数据 将数据写入输出流中
    packet->flags |= AV_PKT_FLAG_KEY;
    packet->stream_index = 0;
    av_interleaved_write_frame(fAVFormatContext, packet);

    packetCnt++;

    if ( packetCnt == vtime )
    {
        packet->dts = 0;
        packet->pts = 0;
        //写入视频尾
        av_write_trailer(fAVFormatContext);
        avcodec_close(fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]->codec);
        av_freep(&fAVFormatContext->streams[0]);
        avio_close(fAVFormatContext->pb);
        av_free(fAVFormatContext);

        packetCnt = 0;
    }
}

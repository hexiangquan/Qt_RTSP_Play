#-------------------------------------------------
#
# Project created by QtCreator 2016-08-15T09:45:17
#
#-------------------------------------------------

QT       += core gui

TARGET = QtRtspVideo
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    Video/rtspthread.cpp \
    Video/qffmpeg.cpp \
    Video/frmmain.cpp

HEADERS  += widget.h \
    Video/rtspthread.h \
    Video/qffmpeg.h \
    Video/frmmain.h

FORMS    += widget.ui \
    Video/frmmain.ui

INCLUDEPATH +=  Video/ffmpeg/include
LIBS += Video/ffmpeg/lib/libavcodec.dll.a \
        Video/ffmpeg/lib/libavfilter.dll.a \
        Video/ffmpeg/lib/libavformat.dll.a \
        Video/ffmpeg/lib/libswscale.dll.a \
        Video/ffmpeg/lib/libavutil.dll.a

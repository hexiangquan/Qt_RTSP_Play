#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //视频显示窗口区域
    pFrmMain = new frmMain(ui->frame);
}

Widget::~Widget()
{
    delete ui;
}

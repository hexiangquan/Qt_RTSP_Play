#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Video/frmmain.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    frmMain *pFrmMain;
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

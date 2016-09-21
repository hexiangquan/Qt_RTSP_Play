/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created: Mon Aug 15 10:52:11 2016
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QLabel *labVideo1;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QString::fromUtf8("frmMain"));
        frmMain->resize(895, 685);
        labVideo1 = new QLabel(frmMain);
        labVideo1->setObjectName(QString::fromUtf8("labVideo1"));
        labVideo1->setGeometry(QRect(0, 0, 895, 685));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labVideo1->sizePolicy().hasHeightForWidth());
        labVideo1->setSizePolicy(sizePolicy);
        labVideo1->setFrameShape(QFrame::Box);
        labVideo1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(frmMain);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "RTSP\346\222\255\346\224\276\345\231\250", 0, QApplication::UnicodeUTF8));
        labVideo1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H

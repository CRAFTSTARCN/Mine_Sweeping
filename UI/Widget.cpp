//
// Created by Ag2S on 2020/8/3.
//

#include "Widget.h"
#include <QScreen>
#include <QPixmap>
#include <QPalette>

Widget::Widget() : QWidget(), SrcWd(0), SrcHt(0) {}

Widget::Widget(QWidget *parent) : QWidget(parent), SrcWd(0), SrcHt(0) {}

void Widget::GetSrcSize() {
    auto src = QApplication::screens()[0];
    auto sz = src->virtualSize();
    SrcWd = sz.width();
    SrcHt = sz.height();
}

void Widget::SelfFit(double rate, int _wd, int _ht) {
    int ht,wd;
    if((double)SrcWd / (double)SrcHt < (double)wd/(double)ht) {
        wd = rate*SrcWd;
        ht = wd* _ht/_wd;
    } else{
        ht = rate*SrcHt;
        wd = ht * _wd/_ht;
    }
    this->setFixedSize(wd,ht);
}

void Widget::SetBackground(QColor backcolor) {
    QPixmap backPixmap;
    backPixmap.fill(backcolor);
    SetBackground(&backPixmap);
}

void  Widget::SetBackground(QPixmap *pix) {
    QPalette back = this->palette();
    back.setBrush(this->backgroundRole(),
                  QBrush(pix->scaled(this->size(),
                                     Qt::IgnoreAspectRatio,
                                     Qt::SmoothTransformation)));
    this->setPalette(back);
    this->setAutoFillBackground(true);
}
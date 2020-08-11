//
// Created by Ag2S on 2020/8/3.
//

#ifndef MINE_SWEEPING_WIDGET_H
#define MINE_SWEEPING_WIDGET_H

#include <QApplication>
#include <QWidget>

class Widget : public QWidget {
Q_OBJECT
protected:
    int SrcWd,SrcHt;
public:
    Widget();
    Widget(QWidget* parent);
    void GetSrcSize();
    void SelfFit(double rate,int _wd, int _ht);
    void SetBackground(QPixmap *pix);
    void SetBackground(QColor backcolor);
};

#endif //MINE_SWEEPING_WIDGET_H

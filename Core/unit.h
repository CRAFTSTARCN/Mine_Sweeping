//
// Created by Ag2S on 2020/8/3.
//

//Unit Class

#ifndef MINE_SWEEPING_UNIT_H
#define MINE_SWEEPING_UNIT_H


#include <QObject>


class unit : public QObject {
    Q_OBJECT
protected:
    enum Status {Normal,Active,Marked} CurrentStatus; //标记状态
    bool isBoom; //标记是否为地雷
    int NeighborBooms; //标记临近单位的炸弹数量
    int line,row; //在雷区的位置
public:
    friend class board;
    unit();
    unit(bool boom,int _i, int _j);
    ~unit();
    int NbBooms() const;
    void check();
    void mark();
    void remark();
    signals: //爆炸，点开但未爆炸、被标记、反标记后的信号
    void boom(unit* me);
    void reflect(unit* me);
    void marking(unit* me);
    void remarking(unit* me);
};

#endif //MINE_SWEEPING_UNIT_H
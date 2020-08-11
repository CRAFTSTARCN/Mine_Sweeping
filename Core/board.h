//
// Created by Ag2S on 2020/8/4.
//

#ifndef MINE_SWEEPING_BOARD_H
#define MINE_SWEEPING_BOARD_H

#include "unit.h"
#include <vector>

class board : public QObject{
    Q_OBJECT
    void SetConnector();
    void SetNeighborBooms(std::vector<int> booms);
protected:
    std::vector<std::vector<unit*>> units;
    int width,height;
    int Remained;
    int GameStatus;
public:
    board(int wd, int ht);
    ~board();
    void reset(int wd, int ht);
    std::vector<int> GotRand();
    void LoseGame(unit* u);
    void WinGame();
    void CheckVictory();
    void Spread(unit* u);
    unit* at(int i, int j) const ;
    signals:
    void OriginalBoomingPoint(int i, int j);
    void losing();
    void wining();
    void resetting(int wd, int ht);
    void BoomPoint(int wd, int ht);
};

#endif //MINE_SWEEPING_BOARD_H
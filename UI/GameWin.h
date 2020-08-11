//
// Created by Ag2S on 2020/8/6.
//

#ifndef MINE_SWEEPING_GAMEWIN_H
#define MINE_SWEEPING_GAMEWIN_H

#include "GameGridButton.h"
#include "../Core/board.h"
#include "Widget.h"
#include <QLabel>
#include <QLayout>
class GameWin : public Widget {
    Q_OBJECT
protected:
    std::vector<std::vector<GameGridButton*>> Buttons;
    QPushButton *Head;
    QLabel *Mention;
    board *BandedBoard;
    Widget *MainBoard;
    QVBoxLayout *GlobalLayout;
    QGridLayout *MainLayout;
    int TarWD, TarHt;
    void DisableAllButton();
    void SetConnection();
    void SpanButtons();

public:
    GameWin(int wd, int ht);
    ~GameWin();
    void ResetGame(int wd, int ht);
    void SafeDestruction();
    void CoreChange();
    void LostGame();
    void WinGame();
    void SetOriBoomPoint(int i, int j);
    void SetNormalBoomPoint(int i, int j);

};

#endif //MINE_SWEEPING_GAMEWIN_H
//
// Created by Ag2S on 2020/8/6.
//

#include "GameWin.h"
#include "QApplication"
#include <QDebug>

GameWin::GameWin(int wd, int ht) : BandedBoard(new board(wd, ht)), Mention(new QLabel), Head(new QPushButton),
MainLayout(new QGridLayout), GlobalLayout(new QVBoxLayout), TarWD(wd), TarHt(ht), MainBoard(nullptr)
{
    GetSrcSize();
    this->setObjectName("Global");
    Head->setFixedSize(SrcWd*0.02,SrcWd*0.02);
    Head->setIconSize(Head->size());
    Mention->setFixedHeight(Head->height());
    GlobalLayout->addWidget(Head, 0, Qt::AlignCenter);
    GlobalLayout->addWidget(Mention,0,Qt::AlignCenter);
    this->setLayout(GlobalLayout);
    ResetGame(wd, ht);
    SetConnection();
}

void GameWin::ResetGame(int wd, int ht) {
    if(MainBoard != nullptr) {
        SafeDestruction();
    }
    Head->setIcon(QIcon(QPixmap("./Pics/Normal_Head.png")));
    Head->setIconSize(Head->size());
    Mention->setText("Exist boom number : " + QString::fromStdString(std::to_string(int(0.15*wd*ht))));
    MainBoard = new Widget;
    MainLayout = new QGridLayout;
    MainLayout->setSpacing(0);
    Buttons.resize(ht,std::vector<GameGridButton*>(wd, nullptr));
    SpanButtons();
    for(int i=0; i<ht;++i){
        for(int j=0; j<wd; ++j) {
            MainLayout->addWidget(Buttons[i][j],i,j,1,1);
        }
    }
    MainBoard->setLayout(MainLayout);
    GlobalLayout->addWidget(MainBoard);
}

void GameWin::SafeDestruction() {
    GlobalLayout->removeWidget(MainBoard);
    auto O_MainBoard = MainBoard;
    auto O_MainLayout = MainLayout;
    MainBoard = nullptr;
    MainLayout = nullptr;
    delete O_MainLayout;
    delete O_MainBoard;
}

void GameWin::SpanButtons() {
    for(int i=0; i<Buttons.size(); ++i) {
        for(int j=0; j<Buttons[i].size(); ++j) {
            Buttons[i][j] = new GameGridButton(BandedBoard->at(i,j));
            Buttons[i][j]->setFixedSize(0.015*SrcWd,0.015*SrcWd);
        }
    }
}

void GameWin::DisableAllButton() {
    for(int i=0 ;i<Buttons.size(); ++i) {
        for(int j=0 ; j<Buttons[i].size(); ++j) {
            Buttons[i][j]->DisableClick();
        }
    }
}

void GameWin::SetConnection() {
    QApplication::connect(Head,&QPushButton::clicked,this,&GameWin::CoreChange);
    QApplication::connect(BandedBoard,&board::resetting,this,&GameWin::ResetGame);
    QApplication::connect(BandedBoard,&board::wining,this,&GameWin::WinGame);
    QApplication::connect(BandedBoard,&board::losing,this,&GameWin::LostGame);
    QApplication::connect(BandedBoard,&board::OriginalBoomingPoint,this,&GameWin::SetOriBoomPoint);
    QApplication::connect(BandedBoard,&board::BoomPoint,this,&GameWin::SetNormalBoomPoint);
}

void GameWin::CoreChange() {
    for(int i=0; i<Buttons.size(); ++i) {
        for(int j=0; j<Buttons[i].size(); ++j) {
            Buttons[i][j]->DeConnection();
        }
    }
    this->BandedBoard->reset(TarWD,TarHt);
}

void GameWin::WinGame() {
    Head->setIcon(QIcon(QPixmap("./Pics/Win_Head.png")));
    Head->setIconSize(Head->size());
    Mention->setText("Victory!");
    DisableAllButton();
}

void  GameWin::LostGame() {
    Head->setIcon(QIcon(QPixmap("./Pics/Booming_Head.png")));
    Head->setIconSize(Head->size());
    Mention->setText("You Lose!");
    DisableAllButton();
}

void GameWin::SetOriBoomPoint(int i, int j) {
    Buttons[i][j]->setStyleSheet("background-color:red");
}

void GameWin::SetNormalBoomPoint(int i, int j) {
    Buttons[i][j]->setStyleSheet("background-color:gray");
}

GameWin::~GameWin() {
    delete BandedBoard;
}
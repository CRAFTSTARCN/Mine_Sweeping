//
// Created by Ag2S on 2020/8/3.
//

#include "GameGridButton.h"

#include <QApplication>
#include <QIcon>
#define Button GameGridButton

void GameGridButton::SetConnections() {
    QApplication::connect(this,&Button::LeftTrigHit,this,&Button::Check);
    QApplication::connect(this,&Button::RightTrigHit,this,&Button::Mark);
    QApplication::connect(BandedUnit,&unit::reflect,this,&Button::Checking);
    QApplication::connect(BandedUnit,&unit::marking,this,&Button::Marking);
    QApplication::connect(BandedUnit,&unit::remarking,this,&Button::Remarking);
    QApplication::connect(BandedUnit,&unit::boom,this,&Button::Booming);
}

void GameGridButton::DeConnection() {
    QApplication::disconnect(BandedUnit,0,this,0);
}

Button::GameGridButton() : Clickable(true), BandedUnit(nullptr) {
    SetConnections();
    this->ChangeSkin("./Pics/Normal_pic.png");
}

Button::GameGridButton(QWidget *parent) : Clickable(true), BandedUnit(nullptr),
                                            QPushButton(parent)
                                            {
                                                SetConnections();
                                                this->ChangeSkin("./Pics/Normal_pic.png");
                                            }

Button::GameGridButton(unit *bdunit) : Clickable(true), BandedUnit(bdunit) {
    if(bdunit == nullptr) {
        throw new std::runtime_error("ERROR:Banded with a null unit");
    }
    SetConnections();
    this->ChangeSkin("./Pics/Normal_pic.png");
}

Button::GameGridButton(unit *bdunit, QWidget *parent) :
                        Clickable(true), BandedUnit(bdunit), QPushButton(parent)
                        {
                            SetConnections();
                            this->ChangeSkin("./Pics/Normal_pic.png");
                        }

Button::~GameGridButton() = default;

void Button::mousePressEvent(QMouseEvent *e) {
    if(!Clickable) return;
    if(Qt::LeftButton == e->button()) {
        emit LeftTrigHit();
    } else if(Qt::RightButton == e->button()) {
        emit RightTrigHit();
    }
}

void Button::Check() {
    BandedUnit->check();
}

void Button::Mark() {
    BandedUnit->mark();
}

void Button::ChangeSkin(const std::string &path) {
    QIcon myskin(QString::fromStdString(path));
    this->setIcon(myskin);
    this->setIconSize(this->size());
}

void Button::Checking() {
    ChangeSkin("./Pics/" + std::to_string(BandedUnit->NbBooms()) + ".png");
}

void Button::Booming() {
    ChangeSkin("./Pics/Booming_Pic.png");
}

void Button::Marking() {
    ChangeSkin("./Pics/Marked_Pic");
}

void Button::Remarking() {
    ChangeSkin("./Pics/Normal_Pic");
}

void Button::DisableClick() {
    this->Clickable = false;
}

void Button::resizeEvent(QResizeEvent *event) {
    this->setIconSize(this->size());
}
//
// Created by Ag2S on 2020/8/3.
//

#ifndef MINE_SWEEPING_GAMEGRIDBUTTON_H
#define MINE_SWEEPING_GAMEGRIDBUTTON_H

#include <../Core/unit.h>
#include <QPushButton>
#include <QMouseEvent>

class GameGridButton : public QPushButton {
    Q_OBJECT
private:
    unit *BandedUnit;
    bool Clickable;
    void SetConnections();

public:
    GameGridButton();
    GameGridButton(QWidget* parent);
    GameGridButton(unit* bdunit);
    GameGridButton(unit* bdunit, QWidget* parent);
    ~GameGridButton();
    void DeConnection();
    void mousePressEvent(QMouseEvent *e);
    void Check();
    void Mark();
    void ChangeSkin(const std::string& path);
    void Booming();
    void Marking();
    void Remarking();
    void Checking();
    void DisableClick();
    void resizeEvent(QResizeEvent *event);
    signals:
    void LeftTrigHit();
    void RightTrigHit();
};

#endif //MINE_SWEEPING_GAMEGRIDBUTTON_H
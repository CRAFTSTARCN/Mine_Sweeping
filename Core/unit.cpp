//
// Created by Ag2S on 2020/8/3.
//

#include "unit.h"

unit::unit() : CurrentStatus(Normal), NeighborBooms(0), isBoom(false) {}

unit::unit(bool boom, int _i, int _j) : CurrentStatus(Normal), NeighborBooms(0), isBoom(boom), line(_i), row(_j) {}

unit::~unit() = default;

int unit::NbBooms() const {
    return NeighborBooms;
}

void unit::check() {
    if(this -> CurrentStatus == Normal) {
        this->CurrentStatus = Active;
        if(this->isBoom) {
            emit boom(this);
        } else {
            emit reflect(this);
        }
    }
}

void unit::mark() {
    if(this->CurrentStatus == Marked) return remark();
    if(this->CurrentStatus == Normal) {
        this->CurrentStatus = Marked;
        emit marking(this);
    }
}

void unit::remark() {
    if(CurrentStatus == Marked) {
        this->CurrentStatus = Normal;
        emit remarking(this);
    }
}
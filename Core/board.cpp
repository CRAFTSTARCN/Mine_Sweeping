//
// Created by Ag2S on 2020/8/4.
//

#include "board.h"
#include <QApplication>
#include <ctime>
#include <algorithm>
#include <functional>

void board::reset(int wd, int ht) {
    width = wd, height = ht;
    if(!units.empty()) {
        for(auto &line : units) {
            for (auto &u : line) {
                delete u;
                u = nullptr;
            }
            std::vector<unit*>().swap(line);
        }
        std::vector<std::vector<unit*>>().swap(units);
    }
    units = std::vector<std::vector<unit*>>(ht,std::vector<unit*>(wd,nullptr));
    std::vector<int> randvect = this->GotRand();
    Remained = width*height - randvect.size();
    for(auto i : randvect) {
        units[i/width][i%width] = new unit(true,i/width,i%width);
    }
    for(int i=0; i<ht; ++i){
        for(int j=0; j<wd; ++j){
            if(units[i][j] == nullptr){
                units[i][j] = new unit(false,i,j);
            }
        }
    }
    GameStatus = 0;
    SetNeighborBooms(randvect);
    SetConnector();
    emit resetting(wd,ht);
}

std::vector<int> board::GotRand() {
    srand(time(NULL));
    int total = width * height;
    std::vector<int> randvect(total,0);
    for(int i=0; i<total; ++i) {
        randvect[i] = i;
    }
    std::random_shuffle(randvect.begin(),randvect.end());
    randvect.resize(int(0.15*total));
    return randvect;
}

void board::SetNeighborBooms(std::vector<int> booms) {
    for(auto b : booms) {
        int posi = b/width, posj = b%width;
        std::vector<std::pair<int,int>> vects = {{1,0},{1,1},{0,1},{-1,1},{-1,0},
                                                {-1,-1},{0,-1},{1,-1}};
        for(auto v : vects) {
            int ni =  posi + v.first, nj = posj + v.second;
            if(ni >= 0&& ni < height && nj >= 0 && nj < width){
                units[ni][nj]->NeighborBooms++;
            }
        }
    }
}

void board::SetConnector() {
    for(int i=0 ;i<height; ++i) {
        for(int j=0; j<width; ++j) {
            if(units[i][j]->isBoom){
                QApplication::connect(units[i][j],&unit::boom,this,&board::LoseGame);
            } else {
                QApplication::connect(units[i][j],&unit::reflect,this,&board::CheckVictory);
                QApplication::connect(units[i][j],&unit::reflect,this,&board::Spread);
            }
        }
    }
}

board::board(int wd, int ht) : width(wd), height(ht), units(std::vector<std::vector<unit*>>()) {
    reset(wd,ht);
}

board::~board() {
    for(auto &line : units) {
        for (auto &u : line) {
            delete u;
            u = nullptr;
        }
    }
}

void board::LoseGame(unit *u) {
    if(GameStatus != 0) return;
    GameStatus = -1;
    emit OriginalBoomingPoint(u->line,u->row);
    for(int i=0; i<height; ++i) {
        for(int j=0; j<width; ++j) {
            if(units[i][j]->isBoom && units[i][j] != u){
                units[i][j] -> check();
                emit BoomPoint(i,j);
            }
        }
    }
    emit losing();
}

void board::WinGame() {
    GameStatus = 1;
    emit wining();
}

void board::CheckVictory() {
    --Remained;
    if(Remained == 0) {
        WinGame();
    }
}

void board::Spread(unit *u) {
    if(u->NbBooms()) return;
    int posi = u->line, posj = u->row;
    std::vector<std::vector<bool>> vis(height,std::vector<bool >(width,0));
    vis[posi][posj] = 1;
    std::function<void(std::vector<std::pair<int,int>>)> bfs;
    bfs = [&](std::vector<std::pair<int,int>> nodes) -> void {
        if(nodes.empty()) return;
        std::vector<std::pair<int,int>> n_nodes;
        std::vector<std::pair<int,int>> vects = {{1,0},{1,1},{0,1},{-1,1},{-1,0},
                                                 {-1,-1},{0,-1},{1,-1}};
        for(int i=0; i<nodes.size(); ++i) {
            for(auto v : vects) {
                int ni = nodes[i].first + v.first;
                int nj = nodes[i].second + v.second;
                if(ni >= 0&& ni < height && nj >= 0 && nj < width && !vis[ni][nj]) {
                    vis[ni][nj] = 1;
                    if(!units[ni][nj]->isBoom) {
                        units[ni][nj]->check();
                        if(units[ni][nj]->NbBooms() == 0) n_nodes.push_back(std::make_pair(ni,nj));
                    }
                }
            }
        }
        return bfs(n_nodes);
    };
    bfs({{posi,posj}});
}

unit * board::at(int i, int j) const {
    return units[i][j];
}
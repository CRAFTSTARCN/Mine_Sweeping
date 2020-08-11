//
// Created by Ag2S on 2020/8/9.
//

#include "Configure.h"
#include <fstream>

Configure::Configure(std::string conf_file) {
    std::ifstream in;
    in.open(conf_file);
    in>>wd>>ht;
    if(wd > 60 || ht > 35) {
        throw new std::runtime_error("Configure ERROR: the game board that you asked is too big");
    }
}

int Configure::Width() const {
    return wd;
}

int Configure::Height() const {
    return ht;
}
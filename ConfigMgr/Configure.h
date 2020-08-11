//
// Created by Ag2S on 2020/8/9.
//

#ifndef MINE_SWEEPING_CONFIGURE_H
#define MINE_SWEEPING_CONFIGURE_H

#include <string>

class Configure {
protected:
    int wd,ht;
public:
    Configure(std::string conf_file);
    int Width() const ;
    int Height() const;
};

#endif //MINE_SWEEPING_CONFIGURE_H
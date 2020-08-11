#include <iostream>
#include "./UI/GameWin.h"
#include "ConfigMgr/Configure.h"
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[]) {
    FreeConsole();
    QApplication app(argc, argv);
    Configure Conf("config.txt");
    GameWin MainWin(Conf.Width(), Conf.Height());
    MainWin.show();
    return QApplication::exec();
}

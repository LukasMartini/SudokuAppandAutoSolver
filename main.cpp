//
// Created by Luke Martin on 2023-04-06.
//
#include "InputWindow.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InputWindow iw {};
    iw.show();
    return app.exec();
}
//
// Created by Luke Martin on 2023-03-29.
//

#include "InputWindow.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
            QApplication::translate("toplevel", "Top-level widget"));
    return app.exec();
}
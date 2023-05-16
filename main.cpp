//
// Created by Luke Martin on 2023-04-06.
//
#include "InputWindow.h"
#include "gtest/gtest.h"
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    InputWindow iw {};
    iw.show();
    return app.exec();
//    GTEST_FLAG_SET(death_test_style, "threadsafe"); // NOTE ABOUT THIS STUFF: return RUN_ALL_TESTS(); is required for gtest to run. Hence, the UI and gtest cannot be run simultaneously as of now.
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
}
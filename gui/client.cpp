//
// Created by 98770 on 2024/5/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_client.h" resolved

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);
    window.setWindowTitle("Simple example");
    window.show();

    return app.exec();
}

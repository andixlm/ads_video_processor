#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setFixedSize(window.size());
    window.show();

    return app.exec();
}

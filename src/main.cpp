#include "interface/mainwidget.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "HELLO, WORLD" << std::endl;
    std::cout << "HELLO, WORLD" << std::endl;
    std::cout << "HELLO, WORLD" << std::endl;
    std::cout << "HELLO, WORLD" << std::endl;
    std::cout << "HELLO, WORLD" << std::endl;
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}

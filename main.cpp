#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.setFixedSize(450, 240);
    w.show();

    return a.exec();
}

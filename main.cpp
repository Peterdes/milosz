#include "miloszqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    miloszqt w;
    w.zaladuj(argv[1]);
    w.show();

    return a.exec();
}

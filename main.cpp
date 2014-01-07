#include "miloszqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	miloszqt w;
	if(argc > 1) w.ustawZrodlo(argv[1]);
	w.show();

	return a.exec();
}

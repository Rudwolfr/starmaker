#include "starmaker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StarMaker w;
	w.show();
	return a.exec();
}

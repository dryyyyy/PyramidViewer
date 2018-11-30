#include "pyramidviewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PyramidViewer w;
	w.show();
	return a.exec();
}

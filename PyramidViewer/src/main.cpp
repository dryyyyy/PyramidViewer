#include "pyramidviewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PyramidViewer pyramidViewer;
	pyramidViewer.show();
	return a.exec();
}

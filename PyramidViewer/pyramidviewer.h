#ifndef PYRAMIDVIEWER_H
#define PYRAMIDVIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_pyramidviewer.h"

class PyramidViewer : public QMainWindow
{
	Q_OBJECT

public:
	PyramidViewer(QWidget *parent = 0);
	~PyramidViewer();

private:
	Ui::PyramidViewerClass ui;
};

#endif // PYRAMIDVIEWER_H

#ifndef PYRAMIDVIEWER_H
#define PYRAMIDVIEWER_H

#include <QtWidgets/QMainWindow>
#include <QComboBox>

#include "imageContainer.h"

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QGroupBox;

class PyramidViewer : public QMainWindow
{
	Q_OBJECT

public:	
	PyramidViewer();
	bool LoadFile(const QString &);
	~PyramidViewer();

private slots:
	void open();

private:	
	void CreateControls();
	void UpdateControls();
	void CreateActions();	
	void UpdateActions();	
	void SetImage(const QImage &newImage);
	void SelectImage(int image);
	void SortLoadedImages(QVector<imageContainer> &vector);


	QLabel *m_mainLabel;
	QLabel *m_imageLabel;
	QScrollArea *m_scrollArea;
	QComboBox *m_loadedImagesComboBox;
	QLabel *m_currentLayerResolution;
	QComboBox *m_imageLayersCombobox;
	QLabel *m_loadedImages;
	QLabel *m_imageLayer;
	imageContainer m_image;
	QVector<imageContainer> m_imageContainerVector;
	QVector<QString> m_imageFilenames;	
	QStringList m_imageLayersList;
	int m_currentImageFlag;
	QStringList m_loadedImagesList;
};

#endif // PYRAMIDVIEWER_H

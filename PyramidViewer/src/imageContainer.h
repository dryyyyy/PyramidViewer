#pragma once
#include <QImage>

class imageContainer
{
private:
	QImage m_image;
	QString m_filename;
	QVector<QImage> m_layers;

	QVector<QImage> createPyramid(QImage image);
	int numberOfLayers(int imageSide);
	
public:
	imageContainer();
	imageContainer(QImage image, QString filename);	
	~imageContainer();
	
	int getWidth();
	int getHeight();
	double getDiagonal();
	QImage getImage();
	QString getFilename();
	QVector<QImage> getImageLayers();

	void setImage(QImage image);

	bool isNull();
};


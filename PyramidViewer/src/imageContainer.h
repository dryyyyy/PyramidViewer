#pragma once
#include <QImage>

class imageContainer
{
private:
	QImage m_image;
	QString m_filename;
	QVector<QImage> m_layers;

	QVector<QImage> CreatePyramid(QImage image);
	int NumberOfLayers(int imageSide);
	
public:
	imageContainer();
	imageContainer(QImage image, QString filename);	
	~imageContainer();
	
	int GetWidth();
	int GetHeight();
	double GetDiagonal();
	QImage GetImage();
	QString GetFilename();
	QVector<QImage> GetImageLayers();

	void SetImage(QImage image);

	bool isNull();
};


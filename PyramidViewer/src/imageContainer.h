#pragma once
#include <QImage>

class ImageContainer
{
public:
	ImageContainer();
	ImageContainer(QImage image, QString filename);
	~ImageContainer();

	int GetWidth();
	int GetHeight();
	double GetDiagonal();
	QImage GetImage();
	QString GetFilename();
	QVector<QImage> GetImageLayers();
	void SetImage(QImage image);
	bool IsNull();

private:
	QVector<QImage> CreatePyramid(QImage image);
	int GetNumberOfLayers(int imageSide);

	QImage m_image;
	QString m_filename;
	QVector<QImage> m_layers;	
};


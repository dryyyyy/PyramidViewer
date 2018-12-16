#pragma once
#include <memory>
#include <QImage>

class ImageContainer
{
public:
	ImageContainer();
	ImageContainer(QImage image, QString filename);
	ImageContainer(const ImageContainer &other);
	ImageContainer& operator=(ImageContainer other);
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
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};


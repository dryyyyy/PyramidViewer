#include <QFileInfo>

#include "imageContainer.h"

QVector<QImage> ImageContainer::CreatePyramid(QImage image)
{
	int imageSide = image.width();
	int length = GetNumberOfLayers(imageSide);
	QVector<QImage> layers;
	layers.push_back(image);

	for (int i = 0; i < length; ++i) {
		imageSide /= 2;
		QImage layer = image.scaled(imageSide, imageSide, Qt::KeepAspectRatio);
		layers.push_back(layer);
	}
	return layers;
}

int ImageContainer::GetNumberOfLayers(int imageSide)
{
	return std::log2(imageSide);
}

ImageContainer::ImageContainer()
{
}

ImageContainer::ImageContainer(QImage image, QString filename)
{
	m_image = image;
	m_filename = filename;
	m_layers = CreatePyramid(image);
}

ImageContainer::~ImageContainer()
{
}

// Getters
int ImageContainer::GetWidth()
{
	return m_image.width();
}

int ImageContainer::GetHeight()
{
	return m_image.height();
}

double ImageContainer::GetDiagonal()
{
	return std::sqrt(m_image.width() * m_image.width() + m_image.height() * m_image.height());
}

QImage ImageContainer::GetImage()
{
	return m_image;
}

QString ImageContainer::GetFilename()
{
	QFileInfo fi(m_filename);
	return fi.fileName();
}

QVector<QImage> ImageContainer::GetImageLayers()
{
	return m_layers;
}

// Setters
void ImageContainer::SetImage(QImage image)
{
	m_image = image;
}



bool ImageContainer::IsNull()
{
	if (m_image.isNull()) {
		return true;
	}
	else {
		return false;
	}

}
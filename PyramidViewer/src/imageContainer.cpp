#include <QFileInfo>

#include "imageContainer.h"

QVector<QImage> imageContainer::CreatePyramid(QImage image)
{
	int imageSide = image.width();
	int length = NumberOfLayers(imageSide);
	QVector<QImage> layers;
	layers.push_back(image);

	for (int i = 0; i < length; ++i) {
		imageSide /= 2;
		QImage layer = image.scaled(imageSide, imageSide, Qt::KeepAspectRatio);
		layers.push_back(layer);
	}
	return layers;
}

int imageContainer::NumberOfLayers(int imageSide)
{
	return std::log2(imageSide);
}

imageContainer::imageContainer()
{
}

imageContainer::imageContainer(QImage image, QString filename)
{
	m_image = image;
	m_filename = filename;
	m_layers = CreatePyramid(image);
}

imageContainer::~imageContainer()
{
}

// Getters
int imageContainer::GetWidth()
{
	return m_image.width();
}

int imageContainer::GetHeight()
{
	return m_image.height();
}

double imageContainer::GetDiagonal()
{
	return std::sqrt(m_image.width() * m_image.width() + m_image.height() * m_image.height());
}

QImage imageContainer::GetImage()
{
	return m_image;
}

QString imageContainer::GetFilename()
{
	QFileInfo fi(m_filename);
	return fi.fileName();
}

QVector<QImage> imageContainer::GetImageLayers()
{
	return m_layers;
}

// Setters
void imageContainer::SetImage(QImage image)
{
	m_image = image;
}



bool imageContainer::isNull()
{
	if (m_image.isNull()) {
		return true;
	}
	else {
		return false;
	}

}
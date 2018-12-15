#include <QFileInfo>

#include "imageContainer.h"

QVector<QImage> imageContainer::createPyramid(QImage image)
{
	int imageSide = image.width();
	int length = numberOfLayers(imageSide);
	QVector<QImage> layers;
	layers.push_back(image);

	for (int i = 0; i < length; ++i) {
		imageSide /= 2;
		QImage layer = image.scaled(imageSide, imageSide, Qt::KeepAspectRatio);
		layers.push_back(layer);
	}
	return layers;
}

int imageContainer::numberOfLayers(int imageSide)
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
	m_layers = createPyramid(image);
}

imageContainer::~imageContainer()
{
}

// Getters
int imageContainer::getWidth()
{
	return m_image.width();
}

int imageContainer::getHeight()
{
	return m_image.height();
}

double imageContainer::getDiagonal()
{
	return std::sqrt(m_image.width() * m_image.width() + m_image.height() * m_image.height());
}

QImage imageContainer::getImage()
{
	return m_image;
}

QString imageContainer::getFilename()
{
	QFileInfo fi(m_filename);
	return fi.fileName();
}

QVector<QImage> imageContainer::getImageLayers()
{
	return m_layers;
}

// Setters
void imageContainer::setImage(QImage image)
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
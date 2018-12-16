#include <QFileInfo>

#include "imageContainer.h"

struct ImageContainer::Impl
{
	Impl(QImage image, QString filename) : m_image(image), m_filename(filename) {
		m_layers = CreatePyramid(image);
	}

	QVector<QImage> CreatePyramid(QImage image);
	int GetNumberOfLayers(int imageSide);

	QImage m_image;
	QString m_filename;
	QVector<QImage> m_layers;


};

QVector<QImage> ImageContainer::Impl::CreatePyramid(QImage image)
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

int ImageContainer::Impl::GetNumberOfLayers(int imageSide)
{
	return std::log2(imageSide);
}

ImageContainer::ImageContainer()
{
}

ImageContainer::ImageContainer(QImage image, QString filename) : pimpl(new Impl(image, filename)) {}

ImageContainer::ImageContainer(const ImageContainer &other) : pimpl(new Impl(*other.pimpl)) {}

ImageContainer& ImageContainer::operator=(ImageContainer other)
{
	swap(pimpl, other.pimpl);
	return *this;
}

ImageContainer::~ImageContainer()
{
}

// Getters
int ImageContainer::GetWidth()
{
	return pimpl->m_image.width();
}

int ImageContainer::GetHeight()
{
	return pimpl->m_image.height();
}

double ImageContainer::GetDiagonal()
{
	return std::sqrt(pimpl->m_image.width() * pimpl->m_image.width() + pimpl->m_image.height() * pimpl->m_image.height());
}

QImage ImageContainer::GetImage()
{
	return pimpl->m_image;
}

QString ImageContainer::GetFilename()
{
	QFileInfo fi(pimpl->m_filename);
	return fi.fileName();
}

QVector<QImage> ImageContainer::GetImageLayers()
{
	return pimpl->m_layers;
}

// Setters
void ImageContainer::SetImage(QImage image)
{
	pimpl->m_image = image;
}



bool ImageContainer::IsNull()
{
	if (pimpl->m_image.isNull()) {
		return true;
	}
	else {
		return false;
	}

}
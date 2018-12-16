#include <QtWidgets>
#include <algorithm>

#include "pyramidviewer.h"

PyramidViewer::PyramidViewer()
	: QMainWindow()
	, m_mainLabel(new QLabel)
	, m_imageLabel(new QLabel)
	, m_scrollArea(new QScrollArea)
	, m_loadedImagesComboBox(new QComboBox)
	, m_currentLayerResolution(new QLabel)
	, m_imageLayersCombobox(new QComboBox)
	, m_loadedImages(new QLabel("File: "))
	, m_imageLayer(new QLabel("Layer: "))
{
	m_imageLabel->setBackgroundRole(QPalette::Base);
	m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_imageLabel->setScaledContents(true);

	m_scrollArea->setBackgroundRole(QPalette::Dark);
	m_scrollArea->setWidget(m_imageLabel);
	m_scrollArea->setVisible(false);
	setCentralWidget(m_mainLabel);

	CreateActions();

	resize(QGuiApplication::primaryScreen()->availableSize() / 2);
}

bool PyramidViewer::LoadFile(const QString &fileName)
{
	QImageReader reader(fileName);
	reader.setAutoTransform(true);
	const QImage newImage = reader.read();
	if (newImage.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1: %2")
			.arg(QDir::toNativeSeparators(fileName), reader.errorString()));
		return false;
	}

	m_image = ImageContainer(newImage, fileName);
	m_imageContainerVector.push_back(m_image);

	SelectImage(m_imageContainerVector.size() - 1);

	SortLoadedImages(m_imageContainerVector);
	
	CreateControls();
	

	m_currentImageFlag = m_loadedImagesList.indexOf(m_image.GetFilename());
	m_loadedImagesComboBox->setCurrentIndex(m_currentImageFlag);

	SetImage(newImage);

	const QString message = tr("Opened \"%1\", %2x%3")
		.arg(QDir::toNativeSeparators(fileName)).arg(m_image.GetWidth()).arg(m_image.GetHeight());
	statusBar()->showMessage(message);

	return true;
}


PyramidViewer::~PyramidViewer()
{

}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
	static bool firstDialog = true;

	if (firstDialog) {
		firstDialog = false;
		const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
		dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
	}

	QStringList mimeTypeFilters;
	mimeTypeFilters << "image/jpeg" << "image/png";
	dialog.setMimeTypeFilters(mimeTypeFilters);
	dialog.selectMimeTypeFilter("image/jpeg");
	if (acceptMode == QFileDialog::AcceptSave)
		dialog.setDefaultSuffix("jpg");
}

void PyramidViewer::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

	while (dialog.exec() == QDialog::Accepted && !LoadFile(dialog.selectedFiles().first())) {}
}

void PyramidViewer::CreateControls()
{
	QWidget *controls = new QWidget;

	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *controlsLayout = new QHBoxLayout;
	QHBoxLayout *controlsLeftLayout = new QHBoxLayout;
	QHBoxLayout *controlsRightLayout = new QHBoxLayout;

	UpdateControls();
	
	controlsLeftLayout->addWidget(m_loadedImages);
	controlsLeftLayout->addWidget(m_loadedImagesComboBox);

	controlsRightLayout->addWidget(m_imageLayer);
	controlsRightLayout->addWidget(m_imageLayersCombobox);
	controlsRightLayout->addWidget(m_currentLayerResolution);

	controlsLayout->addLayout(controlsLeftLayout);
	controlsLayout->addLayout(controlsRightLayout);

	mainLayout->addLayout(controlsLayout);
	mainLayout->addWidget(controls);
	mainLayout->addWidget(m_scrollArea);

	m_mainLabel->setLayout(mainLayout);

	connect(m_loadedImagesComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this,
		[=](int index)
	{
		PyramidViewer::SelectImage(index);
		PyramidViewer::UpdateControls();
		PyramidViewer::SetImage(m_imageContainerVector[index].GetImage());
	});

	connect(m_imageLayersCombobox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
		[=](int index)
	{ 
		PyramidViewer::SetImage(m_imageContainerVector[m_currentImageFlag].GetImageLayers()[index]);
	});
}

void PyramidViewer::UpdateControls()
{
	m_imageLayersList.clear();
	m_imageLayersCombobox->clear();
	for (int i = 0; i < m_imageContainerVector[m_currentImageFlag].GetImageLayers().size(); ++i) {
		m_imageLayersList << QString::number(i);
	}

	m_loadedImagesList.clear();
	for (ImageContainer image : m_imageContainerVector)
	{
		m_loadedImagesList << image.GetFilename();
	}

	m_loadedImagesComboBox->clear();
	m_loadedImagesComboBox->addItems(m_loadedImagesList);

	m_imageLayersCombobox->addItems(m_imageLayersList);
	m_imageLayersCombobox->raise();

	m_loadedImagesComboBox->setCurrentIndex(m_currentImageFlag);
	m_loadedImagesComboBox->raise();
}

void PyramidViewer::SelectImage(int index)
{
	m_currentImageFlag = index;
}

void PyramidViewer::SortLoadedImages(QVector<ImageContainer> &vector)
{
	std::sort(vector.begin(), vector.end(), [](ImageContainer a, ImageContainer b)
	{		
		return a.GetDiagonal() < b.GetDiagonal();
	});
}

void PyramidViewer::CreateActions()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("File"));

	QAction *openAct = fileMenu->addAction(tr("Open"), this, &PyramidViewer::open);
	openAct->setShortcut(QKeySequence::Open);

	QAction *exitAct = fileMenu->addAction(tr("Exit"), this, &QWidget::close);
	exitAct->setShortcut(tr("Ctrl+Q"));
}

void PyramidViewer::UpdateActions()
{
	if (!m_image.IsNull()) {
		m_mainLabel->setVisible(true);
	}
	else {
		m_mainLabel->setVisible(false);
	}	
}

void PyramidViewer::SetImage(const QImage &newImage)
{
	m_image.SetImage(newImage);
	QPixmap pixmap = QPixmap::fromImage(m_image.GetImage());
	m_currentLayerResolution->setText("Size: " + QString::number(m_image.GetWidth()) + "x" + QString::number(m_image.GetHeight()));

	pixmap = pixmap.scaledToWidth(m_imageContainerVector[m_currentImageFlag].GetWidth());

	m_imageLabel->setPixmap(pixmap);

	m_scrollArea->setVisible(true);
	UpdateActions();

	m_imageLabel->adjustSize();
	m_imageLabel->setScaledContents(true);
}
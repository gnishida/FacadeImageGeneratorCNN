#include "ImageGenerationDialog.h"
#include <QFileDialog>

ImageGenerationDialog::ImageGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.lineEditOutputDirectory->setText("C:/Anaconda/caffe/facade/data/images");
	ui.lineEditNumImages->setText("10000");
	ui.lineEditImageSize->setText("227");
	ui.checkBoxGrayscale->setChecked(false);
	ui.lineEditEdgeDisplacement->setText("2");
	ui.lineEditMissingWindows->setText("10");
	ui.lineEditNumFloorsMin->setText("4");
	ui.lineEditNumFloorsMax->setText("20");
	ui.lineEditNumColumnsMin->setText("4");
	ui.lineEditNumColumnsMax->setText("20");

	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

ImageGenerationDialog::~ImageGenerationDialog() {
}

void ImageGenerationDialog::onOutputDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutputDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutputDirectory->setText(dir);
	}
}

void ImageGenerationDialog::onOK() {
	accept();
}

void ImageGenerationDialog::onCancel() {
	reject();
}

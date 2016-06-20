#include "ParameterEstimationDialog.h"
#include <QFileDialog>

ParameterEstimationDialog::ParameterEstimationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	QButtonGroup* group1 = new QButtonGroup();
	group1->addButton(ui.radioButtonCameraTypeStreetView);
	group1->addButton(ui.radioButtonCameraTypeAerialView);

	QButtonGroup* group2 = new QButtonGroup();
	group2->addButton(ui.radioButtonRefineFromBest);
	group2->addButton(ui.radioButtonRefineFromAll);

	ui.checkBoxAutomaticRecognition->setChecked(true);
	ui.lineEditGrammarSnippet->setText("1");
	ui.lineEditGrammarSnippet->setEnabled(false);
	ui.checkBoxCentering3D->setChecked(true);
	ui.checkBoxMeanSubtraction->setChecked(false);
	ui.radioButtonCameraTypeStreetView->setChecked(false);
	ui.radioButtonCameraTypeAerialView->setChecked(true);
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("30");
	ui.lineEditXrotMax->setText("60");
	ui.lineEditYrotMin->setText("30");
	ui.lineEditYrotMax->setText("60");
	ui.lineEditFovMin->setText("20");
	ui.lineEditFovMax->setText("30");
	ui.checkBoxTryMultiples->setChecked(true);
	ui.lineEditNumMultipleTries->setText("5");
	ui.lineEditMaxNoise->setText("2");
	ui.checkBoxRefinement->setChecked(true);
	ui.radioButtonRefineFromBest->setChecked(true);
	ui.radioButtonRefineFromAll->setChecked(false);
	ui.checkBoxApplyTexture->setChecked(false);

	connect(ui.checkBoxAutomaticRecognition, SIGNAL(clicked()), this, SLOT(onAutomaticRecognition()));
	connect(ui.checkBoxTryMultiples, SIGNAL(clicked()), this, SLOT(onTryMultiples()));
	connect(ui.checkBoxRefinement, SIGNAL(clicked()), this, SLOT(onRefinement()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

ParameterEstimationDialog::~ParameterEstimationDialog() {
}

void ParameterEstimationDialog::onAutomaticRecognition() {
	ui.lineEditGrammarSnippet->setEnabled(ui.checkBoxAutomaticRecognition->isChecked());
}

void ParameterEstimationDialog::onTryMultiples() {
	ui.lineEditNumMultipleTries->setEnabled(ui.checkBoxTryMultiples->isChecked());
	ui.lineEditMaxNoise->setEnabled(ui.checkBoxTryMultiples->isChecked());
}

void ParameterEstimationDialog::onRefinement() {
	ui.radioButtonRefineFromBest->setEnabled(ui.checkBoxRefinement->isChecked());
	ui.radioButtonRefineFromAll->setEnabled(ui.checkBoxRefinement->isChecked());
}

void ParameterEstimationDialog::onOK() {
	accept();
}

void ParameterEstimationDialog::onCancel() {
	reject();
}

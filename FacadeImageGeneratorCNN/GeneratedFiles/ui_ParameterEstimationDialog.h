/********************************************************************************
** Form generated from reading UI file 'ParameterEstimationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERESTIMATIONDIALOG_H
#define UI_PARAMETERESTIMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ParameterEstimationDialog
{
public:
    QLabel *label_11;
    QLineEdit *lineEditFovMax;
    QLineEdit *lineEditYrotMin;
    QLineEdit *lineEditXrotMin;
    QLabel *label_13;
    QLineEdit *lineEditYrotMax;
    QLineEdit *lineEditXrotMax;
    QLabel *label_14;
    QLabel *label_10;
    QLineEdit *lineEditCameraDistance;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *lineEditFovMin;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QLabel *label_12;
    QRadioButton *radioButtonCameraTypeStreetView;
    QRadioButton *radioButtonCameraTypeAerialView;
    QCheckBox *checkBoxCentering3D;
    QCheckBox *checkBoxMeanSubtraction;
    QLabel *label_15;
    QLineEdit *lineEditGrammarSnippet;
    QLabel *label_16;
    QCheckBox *checkBoxApplyTexture;
    QCheckBox *checkBoxRefinement;
    QCheckBox *checkBoxTryMultiples;
    QLabel *label_17;
    QLineEdit *lineEditNumMultipleTries;
    QLabel *label_18;
    QLineEdit *lineEditMaxNoise;
    QRadioButton *radioButtonRefineFromBest;
    QRadioButton *radioButtonRefineFromAll;
    QLabel *label_19;
    QCheckBox *checkBoxAutomaticRecognition;

    void setupUi(QDialog *ParameterEstimationDialog)
    {
        if (ParameterEstimationDialog->objectName().isEmpty())
            ParameterEstimationDialog->setObjectName(QStringLiteral("ParameterEstimationDialog"));
        ParameterEstimationDialog->resize(502, 353);
        label_11 = new QLabel(ParameterEstimationDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(173, 190, 16, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditFovMax = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMax->setObjectName(QStringLiteral("lineEditFovMax"));
        lineEditFovMax->setGeometry(QRect(200, 190, 61, 20));
        lineEditYrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMin->setObjectName(QStringLiteral("lineEditYrotMin"));
        lineEditYrotMin->setGeometry(QRect(110, 160, 61, 20));
        lineEditXrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMin->setObjectName(QStringLiteral("lineEditXrotMin"));
        lineEditXrotMin->setGeometry(QRect(110, 130, 61, 20));
        label_13 = new QLabel(ParameterEstimationDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(173, 130, 16, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditYrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMax->setObjectName(QStringLiteral("lineEditYrotMax"));
        lineEditYrotMax->setGeometry(QRect(200, 160, 61, 20));
        lineEditXrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMax->setObjectName(QStringLiteral("lineEditXrotMax"));
        lineEditXrotMax->setGeometry(QRect(200, 130, 61, 20));
        label_14 = new QLabel(ParameterEstimationDialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(173, 160, 16, 20));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(ParameterEstimationDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(30, 190, 71, 16));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditCameraDistance = new QLineEdit(ParameterEstimationDialog);
        lineEditCameraDistance->setObjectName(QStringLiteral("lineEditCameraDistance"));
        lineEditCameraDistance->setGeometry(QRect(110, 100, 61, 20));
        label_7 = new QLabel(ParameterEstimationDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 100, 91, 20));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(ParameterEstimationDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 130, 71, 16));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(ParameterEstimationDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 160, 71, 16));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditFovMin = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMin->setObjectName(QStringLiteral("lineEditFovMin"));
        lineEditFovMin->setGeometry(QRect(110, 190, 61, 20));
        pushButtonCancel = new QPushButton(ParameterEstimationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(390, 310, 91, 31));
        pushButtonOK = new QPushButton(ParameterEstimationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(290, 310, 91, 31));
        label_12 = new QLabel(ParameterEstimationDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(30, 70, 71, 16));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        radioButtonCameraTypeStreetView = new QRadioButton(ParameterEstimationDialog);
        radioButtonCameraTypeStreetView->setObjectName(QStringLiteral("radioButtonCameraTypeStreetView"));
        radioButtonCameraTypeStreetView->setGeometry(QRect(110, 70, 82, 17));
        radioButtonCameraTypeAerialView = new QRadioButton(ParameterEstimationDialog);
        radioButtonCameraTypeAerialView->setObjectName(QStringLiteral("radioButtonCameraTypeAerialView"));
        radioButtonCameraTypeAerialView->setGeometry(QRect(210, 70, 82, 17));
        checkBoxCentering3D = new QCheckBox(ParameterEstimationDialog);
        checkBoxCentering3D->setObjectName(QStringLiteral("checkBoxCentering3D"));
        checkBoxCentering3D->setGeometry(QRect(110, 40, 91, 17));
        checkBoxMeanSubtraction = new QCheckBox(ParameterEstimationDialog);
        checkBoxMeanSubtraction->setObjectName(QStringLiteral("checkBoxMeanSubtraction"));
        checkBoxMeanSubtraction->setGeometry(QRect(220, 40, 121, 17));
        label_15 = new QLabel(ParameterEstimationDialog);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 10, 91, 20));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditGrammarSnippet = new QLineEdit(ParameterEstimationDialog);
        lineEditGrammarSnippet->setObjectName(QStringLiteral("lineEditGrammarSnippet"));
        lineEditGrammarSnippet->setGeometry(QRect(250, 10, 31, 20));
        label_16 = new QLabel(ParameterEstimationDialog);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(290, 10, 41, 20));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxApplyTexture = new QCheckBox(ParameterEstimationDialog);
        checkBoxApplyTexture->setObjectName(QStringLiteral("checkBoxApplyTexture"));
        checkBoxApplyTexture->setGeometry(QRect(110, 280, 91, 17));
        checkBoxRefinement = new QCheckBox(ParameterEstimationDialog);
        checkBoxRefinement->setObjectName(QStringLiteral("checkBoxRefinement"));
        checkBoxRefinement->setGeometry(QRect(110, 250, 91, 17));
        checkBoxTryMultiples = new QCheckBox(ParameterEstimationDialog);
        checkBoxTryMultiples->setObjectName(QStringLiteral("checkBoxTryMultiples"));
        checkBoxTryMultiples->setGeometry(QRect(110, 220, 91, 17));
        label_17 = new QLabel(ParameterEstimationDialog);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(210, 220, 31, 16));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditNumMultipleTries = new QLineEdit(ParameterEstimationDialog);
        lineEditNumMultipleTries->setObjectName(QStringLiteral("lineEditNumMultipleTries"));
        lineEditNumMultipleTries->setGeometry(QRect(250, 220, 61, 20));
        label_18 = new QLabel(ParameterEstimationDialog);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(330, 220, 61, 16));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditMaxNoise = new QLineEdit(ParameterEstimationDialog);
        lineEditMaxNoise->setObjectName(QStringLiteral("lineEditMaxNoise"));
        lineEditMaxNoise->setGeometry(QRect(400, 220, 41, 20));
        radioButtonRefineFromBest = new QRadioButton(ParameterEstimationDialog);
        radioButtonRefineFromBest->setObjectName(QStringLiteral("radioButtonRefineFromBest"));
        radioButtonRefineFromBest->setGeometry(QRect(240, 250, 91, 17));
        radioButtonRefineFromAll = new QRadioButton(ParameterEstimationDialog);
        radioButtonRefineFromAll->setObjectName(QStringLiteral("radioButtonRefineFromAll"));
        radioButtonRefineFromAll->setGeometry(QRect(360, 250, 82, 17));
        label_19 = new QLabel(ParameterEstimationDialog);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(446, 220, 21, 20));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxAutomaticRecognition = new QCheckBox(ParameterEstimationDialog);
        checkBoxAutomaticRecognition->setObjectName(QStringLiteral("checkBoxAutomaticRecognition"));
        checkBoxAutomaticRecognition->setGeometry(QRect(110, 10, 131, 17));
        QWidget::setTabOrder(checkBoxAutomaticRecognition, lineEditGrammarSnippet);
        QWidget::setTabOrder(lineEditGrammarSnippet, checkBoxCentering3D);
        QWidget::setTabOrder(checkBoxCentering3D, checkBoxMeanSubtraction);
        QWidget::setTabOrder(checkBoxMeanSubtraction, radioButtonCameraTypeStreetView);
        QWidget::setTabOrder(radioButtonCameraTypeStreetView, radioButtonCameraTypeAerialView);
        QWidget::setTabOrder(radioButtonCameraTypeAerialView, lineEditCameraDistance);
        QWidget::setTabOrder(lineEditCameraDistance, lineEditXrotMin);
        QWidget::setTabOrder(lineEditXrotMin, lineEditXrotMax);
        QWidget::setTabOrder(lineEditXrotMax, lineEditYrotMin);
        QWidget::setTabOrder(lineEditYrotMin, lineEditYrotMax);
        QWidget::setTabOrder(lineEditYrotMax, lineEditFovMin);
        QWidget::setTabOrder(lineEditFovMin, lineEditFovMax);
        QWidget::setTabOrder(lineEditFovMax, checkBoxTryMultiples);
        QWidget::setTabOrder(checkBoxTryMultiples, lineEditNumMultipleTries);
        QWidget::setTabOrder(lineEditNumMultipleTries, lineEditMaxNoise);
        QWidget::setTabOrder(lineEditMaxNoise, checkBoxRefinement);
        QWidget::setTabOrder(checkBoxRefinement, radioButtonRefineFromBest);
        QWidget::setTabOrder(radioButtonRefineFromBest, radioButtonRefineFromAll);
        QWidget::setTabOrder(radioButtonRefineFromAll, checkBoxApplyTexture);
        QWidget::setTabOrder(checkBoxApplyTexture, pushButtonOK);
        QWidget::setTabOrder(pushButtonOK, pushButtonCancel);

        retranslateUi(ParameterEstimationDialog);

        QMetaObject::connectSlotsByName(ParameterEstimationDialog);
    } // setupUi

    void retranslateUi(QDialog *ParameterEstimationDialog)
    {
        ParameterEstimationDialog->setWindowTitle(QApplication::translate("ParameterEstimationDialog", "ParameterEstimationDialog", 0));
        label_11->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_13->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_14->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_10->setText(QApplication::translate("ParameterEstimationDialog", "Field of view:", 0));
        label_7->setText(QApplication::translate("ParameterEstimationDialog", "Camera distance:", 0));
        label_6->setText(QApplication::translate("ParameterEstimationDialog", "Xrot:", 0));
        label_8->setText(QApplication::translate("ParameterEstimationDialog", "Yrot:", 0));
        pushButtonCancel->setText(QApplication::translate("ParameterEstimationDialog", "Cancel", 0));
        pushButtonOK->setText(QApplication::translate("ParameterEstimationDialog", "OK", 0));
        label_12->setText(QApplication::translate("ParameterEstimationDialog", "Camera type:", 0));
        radioButtonCameraTypeStreetView->setText(QApplication::translate("ParameterEstimationDialog", "Street view", 0));
        radioButtonCameraTypeAerialView->setText(QApplication::translate("ParameterEstimationDialog", "Aerial view", 0));
        checkBoxCentering3D->setText(QApplication::translate("ParameterEstimationDialog", "3D Centering", 0));
        checkBoxMeanSubtraction->setText(QApplication::translate("ParameterEstimationDialog", "Mean subtraction", 0));
        label_15->setText(QApplication::translate("ParameterEstimationDialog", "Grammar snippet:", 0));
        label_16->setText(QApplication::translate("ParameterEstimationDialog", "(1 - 14)", 0));
        checkBoxApplyTexture->setText(QApplication::translate("ParameterEstimationDialog", "Apply Texture", 0));
        checkBoxRefinement->setText(QApplication::translate("ParameterEstimationDialog", "Refinement", 0));
        checkBoxTryMultiples->setText(QApplication::translate("ParameterEstimationDialog", "Try Multiples", 0));
        label_17->setText(QApplication::translate("ParameterEstimationDialog", "# Tries:", 0));
        label_18->setText(QApplication::translate("ParameterEstimationDialog", "Max Noise:", 0));
        radioButtonRefineFromBest->setText(QApplication::translate("ParameterEstimationDialog", "From Best one", 0));
        radioButtonRefineFromAll->setText(QApplication::translate("ParameterEstimationDialog", "From All", 0));
        label_19->setText(QApplication::translate("ParameterEstimationDialog", "%", 0));
        checkBoxAutomaticRecognition->setText(QApplication::translate("ParameterEstimationDialog", "Automatic recognition", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterEstimationDialog: public Ui_ParameterEstimationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERESTIMATIONDIALOG_H

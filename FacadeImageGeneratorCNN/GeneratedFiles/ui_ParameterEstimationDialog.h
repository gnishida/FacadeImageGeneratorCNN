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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParameterEstimationDialog
{
public:
    QLineEdit *lineEditTestDataDirectory;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QLabel *label_12;
    QLabel *label_15;
    QPushButton *pushButtonTestDataDirectory;
    QLineEdit *lineEditClassificationDirectory;
    QLabel *label_16;
    QLineEdit *lineEditRegressionDirectory;
    QPushButton *pushButtonClassificationDirectory;
    QPushButton *pushButtonRegressionDirectory;
    QLabel *label_17;
    QLineEdit *lineEditOutputDirectory;
    QPushButton *pushButtonOutputDirectory;
    QLabel *label_18;
    QLineEdit *lineEditNumFloorsMin;
    QLineEdit *lineEditNumFloorsMax;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *lineEditNumColumnsMax;
    QLineEdit *lineEditNumColumnsMin;
    QLabel *label_21;

    void setupUi(QDialog *ParameterEstimationDialog)
    {
        if (ParameterEstimationDialog->objectName().isEmpty())
            ParameterEstimationDialog->setObjectName(QStringLiteral("ParameterEstimationDialog"));
        ParameterEstimationDialog->resize(522, 232);
        lineEditTestDataDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditTestDataDirectory->setObjectName(QStringLiteral("lineEditTestDataDirectory"));
        lineEditTestDataDirectory->setGeometry(QRect(130, 10, 341, 20));
        pushButtonCancel = new QPushButton(ParameterEstimationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(410, 190, 91, 31));
        pushButtonOK = new QPushButton(ParameterEstimationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(310, 190, 91, 31));
        label_12 = new QLabel(ParameterEstimationDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 40, 121, 20));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(ParameterEstimationDialog);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 10, 101, 20));
        label_15->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonTestDataDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonTestDataDirectory->setObjectName(QStringLiteral("pushButtonTestDataDirectory"));
        pushButtonTestDataDirectory->setGeometry(QRect(480, 10, 31, 23));
        lineEditClassificationDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditClassificationDirectory->setObjectName(QStringLiteral("lineEditClassificationDirectory"));
        lineEditClassificationDirectory->setGeometry(QRect(130, 40, 341, 20));
        label_16 = new QLabel(ParameterEstimationDialog);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 70, 121, 20));
        lineEditRegressionDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditRegressionDirectory->setObjectName(QStringLiteral("lineEditRegressionDirectory"));
        lineEditRegressionDirectory->setGeometry(QRect(130, 70, 341, 20));
        pushButtonClassificationDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonClassificationDirectory->setObjectName(QStringLiteral("pushButtonClassificationDirectory"));
        pushButtonClassificationDirectory->setGeometry(QRect(480, 40, 31, 23));
        pushButtonRegressionDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonRegressionDirectory->setObjectName(QStringLiteral("pushButtonRegressionDirectory"));
        pushButtonRegressionDirectory->setGeometry(QRect(480, 70, 31, 23));
        label_17 = new QLabel(ParameterEstimationDialog);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 100, 121, 20));
        lineEditOutputDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(130, 100, 341, 20));
        pushButtonOutputDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(480, 100, 31, 23));
        label_18 = new QLabel(ParameterEstimationDialog);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 130, 121, 20));
        lineEditNumFloorsMin = new QLineEdit(ParameterEstimationDialog);
        lineEditNumFloorsMin->setObjectName(QStringLiteral("lineEditNumFloorsMin"));
        lineEditNumFloorsMin->setGeometry(QRect(130, 130, 51, 20));
        lineEditNumFloorsMax = new QLineEdit(ParameterEstimationDialog);
        lineEditNumFloorsMax->setObjectName(QStringLiteral("lineEditNumFloorsMax"));
        lineEditNumFloorsMax->setGeometry(QRect(200, 130, 51, 20));
        label_19 = new QLabel(ParameterEstimationDialog);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(186, 130, 16, 20));
        label_20 = new QLabel(ParameterEstimationDialog);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 160, 121, 20));
        lineEditNumColumnsMax = new QLineEdit(ParameterEstimationDialog);
        lineEditNumColumnsMax->setObjectName(QStringLiteral("lineEditNumColumnsMax"));
        lineEditNumColumnsMax->setGeometry(QRect(200, 160, 51, 20));
        lineEditNumColumnsMin = new QLineEdit(ParameterEstimationDialog);
        lineEditNumColumnsMin->setObjectName(QStringLiteral("lineEditNumColumnsMin"));
        lineEditNumColumnsMin->setGeometry(QRect(130, 160, 51, 20));
        label_21 = new QLabel(ParameterEstimationDialog);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(186, 160, 16, 20));
        QWidget::setTabOrder(lineEditTestDataDirectory, pushButtonOK);
        QWidget::setTabOrder(pushButtonOK, pushButtonCancel);

        retranslateUi(ParameterEstimationDialog);

        QMetaObject::connectSlotsByName(ParameterEstimationDialog);
    } // setupUi

    void retranslateUi(QDialog *ParameterEstimationDialog)
    {
        ParameterEstimationDialog->setWindowTitle(QApplication::translate("ParameterEstimationDialog", "ParameterEstimationDialog", 0));
        pushButtonCancel->setText(QApplication::translate("ParameterEstimationDialog", "Cancel", 0));
        pushButtonOK->setText(QApplication::translate("ParameterEstimationDialog", "OK", 0));
        label_12->setText(QApplication::translate("ParameterEstimationDialog", "Classification directory:", 0));
        label_15->setText(QApplication::translate("ParameterEstimationDialog", "Test data directory:", 0));
        pushButtonTestDataDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_16->setText(QApplication::translate("ParameterEstimationDialog", "Regression directory:", 0));
        pushButtonClassificationDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        pushButtonRegressionDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_17->setText(QApplication::translate("ParameterEstimationDialog", "Output directory:", 0));
        pushButtonOutputDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_18->setText(QApplication::translate("ParameterEstimationDialog", "#floors:", 0));
        label_19->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_20->setText(QApplication::translate("ParameterEstimationDialog", "#columns:", 0));
        label_21->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterEstimationDialog: public Ui_ParameterEstimationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERESTIMATIONDIALOG_H

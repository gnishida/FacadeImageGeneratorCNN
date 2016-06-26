#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <opencv2/opencv.hpp>

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	Ui::MainWindowClass ui;

public:
	MainWindow(QWidget *parent = 0);

	void generateTrainingImages();
	cv::Mat generateFacadeStructure(int facade_gramamr_id, int width, int height, std::vector<float>& params, int window_displacement, float window_prob = 1);
	void parameterEstimation();

public slots:
	void onGenerateTrainingImages();
	void onParameterEstimation();
};

#endif // MAINWINDOW_H

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
	cv::Mat generateFacadeStructure(int facade_gramamr_id, int width, int height, std::vector<float>& params, int window_displacement, bool noise, int edge_displacement = 0, float box_prob = 1, float edge_prob = 1, float noise_prob = 0, float noise_length = 0);
	void parameterEstimation();

public slots:
	void onGenerateTrainingImages();
	void onParameterEstimation();
};

#endif // MAINWINDOW_H

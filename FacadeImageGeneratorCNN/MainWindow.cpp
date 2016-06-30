#include "MainWindow.h"
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include "Classifier.h"
#include "Regression.h"
#include "Utils.h"
#include "ImageGenerationDialog.h"
#include "ParameterEstimationDialog.h"""
#include "facadeA.h"
#include "facadeB.h"
#include "facadeC.h"
#include "facadeD.h"
#include <boost/algorithm/string.hpp>

#ifndef SQR
#define SQR(x)	((x) * (x))
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionGenerateTrainingImages, SIGNAL(triggered()), this, SLOT(onGenerateTrainingImages()));
	connect(ui.actionParameterEstimation, SIGNAL(triggered()), this, SLOT(onParameterEstimation()));
}

void MainWindow::onGenerateTrainingImages() {
	generateTrainingImages();
}

/**
* This is called when the user clickes [Tool] -> [Predict]
*/
void MainWindow::onParameterEstimation() {
	parameterEstimation();
}

void MainWindow::generateTrainingImages() {
	ImageGenerationDialog dlg;
	if (!dlg.exec()) return;

	std::string DATA_ROOT = dlg.ui.lineEditOutputDirectory->text().toUtf8().constData();
	int NUM_IMAGES_PER_SNIPPET = dlg.ui.lineEditNumImages->text().toInt();
	int IMAGE_SIZE = dlg.ui.lineEditImageSize->text().toInt();
	bool GRAYSCALE = dlg.ui.checkBoxGrayscale->isChecked();
	float EDGE_DISPLACEMENT = dlg.ui.lineEditEdgeDisplacement->text().toFloat();
	float MISSING_WINDOWS = dlg.ui.lineEditMissingWindows->text().toFloat() * 0.01;
	std::pair<int, int> range_NF = std::make_pair(dlg.ui.lineEditNumFloorsMin->text().toInt(), dlg.ui.lineEditNumFloorsMax->text().toInt());
	std::pair<int, int> range_NC = std::make_pair(dlg.ui.lineEditNumColumnsMin->text().toInt(), dlg.ui.lineEditNumColumnsMax->text().toInt());

	boost::filesystem::path dir(DATA_ROOT);
	boost::filesystem::create_directory(dir);

	for (int facade_grammar_id = 0; facade_grammar_id < 4; ++facade_grammar_id) {
		srand(0);

		char dirname[256];
		sprintf(dirname, (DATA_ROOT + "/%02d/").c_str(), facade_grammar_id + 1);
		boost::filesystem::path dir(dirname);
		boost::filesystem::create_directory(dir);

		int subdir_id = -1;

		std::ofstream out((std::string(dirname) + "parameters.txt").c_str());

		printf("Grammar snippet #%d:", facade_grammar_id + 1);
		for (int iter = 0; iter < NUM_IMAGES_PER_SNIPPET; ++iter) {
			printf("\rGrammar snippet #%d: %d", facade_grammar_id + 1, iter + 1);

			if (iter % 100000 == 0) {
				subdir_id++;
				char subdirname[256];
				sprintf(subdirname, (std::string(dirname) + "%03d").c_str(), subdir_id);
				boost::filesystem::path subdir(subdirname);
				boost::filesystem::create_directory(subdir);
			}

			std::vector<float> params;
			cv::Mat img = generateFacadeStructure(facade_grammar_id, IMAGE_SIZE, IMAGE_SIZE, range_NF, range_NC, params, EDGE_DISPLACEMENT, 1 - MISSING_WINDOWS);

			if (GRAYSCALE) {
				cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
			}

			///////////////////////////////////////////////////
			// save the image to the file
			char filename[256];
			sprintf(filename, (std::string(dirname) + "%03d/%06d.png").c_str(), subdir_id, iter);
			cv::imwrite(filename, img);

			for (int i = 0; i < params.size(); ++i) {
				if (i > 0) out << ",";
				out << params[i];
			}
			out << std::endl;
		}
		printf("\n");

		out.close();
	}
	printf("\n");
}

cv::Mat MainWindow::generateFacadeStructure(int facade_gramamr_id, int width, int height, const std::pair<int, int>& range_NF, const std::pair<int, int>& range_NC, std::vector<float>& params, int window_displacement, float window_prob) {
	int thickness = 1;
	//int thickness = utils::uniform_rand(1, 4);

	cv::Mat result;
	if (facade_gramamr_id == 0) {
		result = generateRandomFacadeA(width, height, thickness, range_NF, range_NC, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 1) {
		result = generateRandomFacadeB(width, height, thickness, range_NF, range_NC, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 2) {
		result = generateRandomFacadeC(width, height, thickness, range_NF, range_NC, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 3) {
		result = generateRandomFacadeD(width, height, thickness, range_NF, range_NC, params, window_displacement, window_prob);
	}

	return result;
}

void MainWindow::parameterEstimation() {
	ParameterEstimationDialog dlg;
	if (!dlg.exec()) return;

	boost::filesystem::path results_dir("results/");
	boost::filesystem::create_directory(results_dir);

	std::pair<int, int> range_NF = std::make_pair(dlg.ui.lineEditNumFloorsMin->text().toInt(), dlg.ui.lineEditNumFloorsMax->text().toInt());
	std::pair<int, int> range_NC = std::make_pair(dlg.ui.lineEditNumColumnsMin->text().toInt(), dlg.ui.lineEditNumColumnsMax->text().toInt());

	Classifier classifier((dlg.ui.lineEditClassificationDirectory->text() + "/model/deploy.prototxt").toUtf8().constData(), (dlg.ui.lineEditClassificationDirectory->text() + "/model/train_iter_20000.caffemodel").toUtf8().constData(), (dlg.ui.lineEditClassificationDirectory->text() + "/data/mean.binaryproto").toUtf8().constData());
	std::vector<Regression*> regressions(4);
	for (int i = 0; i < 4; ++i) {
		char deploy_name[256];
		sprintf(deploy_name, (dlg.ui.lineEditRegressionDirectory->text() + "/model/deploy_%02d.prototxt").toUtf8().constData(), i + 1);
		char model_name[256];
		sprintf(model_name, (dlg.ui.lineEditRegressionDirectory->text() + "/model/train_%02d_iter_80000.caffemodel").toUtf8().constData(), i + 1);
		regressions[i] = new Regression(deploy_name, model_name);
	}

	int correct_classification = 0;
	int incorrect_classification = 0;

	// read the ground truth of parameter values
	std::map<int, std::vector<std::vector<float>>> params_truth;
	for (int i = 0; i < 4; ++i) {
		params_truth[i] = std::vector<std::vector<float>>();

		char file_path[256];
		sprintf(file_path, (dlg.ui.lineEditTestDataDirectory->text() + "/images/%02d/parameters.txt").toUtf8().constData(), i + 1);
		std::ifstream in_params(file_path);
		while (true) {
			std::string line;
			std::getline(in_params, line);
			if (line.empty()) break;

			std::vector<std::string> strs;
			boost::split(strs, line, boost::is_any_of(","));

			std::vector<float> values;
			for (int j = 0; j < strs.size(); ++j) {
				values.push_back(stof(strs[j]));
			}

			params_truth[i].push_back(values);
		}
	}

	std::map<int, std::vector<float>> rmse;
	std::map<int, int> rmse_count;

	std::ifstream in((dlg.ui.lineEditTestDataDirectory->text() + "/test.txt").toUtf8().constData());
	int iter = 0;
	while (true) {
		std::string line;
		std::getline(in, line);
		int index = line.find(" ");
		if (index == std::string::npos) break;

		std::string file_path = line.substr(0, index);
		int grammar_id = std::stoi(line.substr(index + 1));

		// read the test image
		cv::Mat img = cv::imread((std::string((dlg.ui.lineEditTestDataDirectory->text() + "/images/").toUtf8().constData()) + file_path).c_str());

		// convert the image to grayscale with 128x128 size
		cv::Mat grayImg;
		cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
		cv::resize(grayImg, grayImg, cv::Size(128, 128));
		cv::threshold(grayImg, grayImg, 230, 255, cv::THRESH_BINARY);

		// classification
		std::vector<Prediction> predictions = classifier.Classify(img, 4);
		if (predictions[0].first == grammar_id) correct_classification++;
		else incorrect_classification++;

		// parameter estimation
		std::vector<float> predicted_params = regressions[grammar_id]->Predict(grayImg);

		// obtain file id
		int index1 = file_path.rfind("/");
		int index2 = file_path.find(".", index1);
		int file_id = stoi(file_path.substr(index1 + 1, index2 - index1 - 1));

		// 誤差を計算
		if (predictions[0].first == grammar_id) {
			if (rmse[grammar_id].size() == 0) {
				rmse[grammar_id].resize(predicted_params.size(), 0);
				rmse_count[grammar_id] = 0;
			}

			for (int i = 0; i < predicted_params.size(); ++i) {
				rmse[grammar_id][i] += SQR(params_truth[grammar_id][file_id][i] - predicted_params[i]);
			}
			rmse_count[grammar_id]++;
		}

		// predictされた画像を作成する
		cv::Mat predicted_img;
		if (predictions[0].first == 0) {
			predicted_img = generateFacadeA(img.cols, img.rows, 2, range_NF, range_NC, predicted_params);
		}
		else if (predictions[0].first == 1) {
			predicted_img = generateFacadeB(img.cols, img.rows, 2, range_NF, range_NC, predicted_params);
		}
		else if (predictions[0].first == 2) {
			predicted_img = generateFacadeC(img.cols, img.rows, 2, range_NF, range_NC, predicted_params);
		}
		else if (predictions[0].first == 3) {
			predicted_img = generateFacadeD(img.cols, img.rows, 2, range_NF, range_NC, predicted_params);
		}

		// make the predicted image blue
		for (int r = 0; r < predicted_img.rows; ++r) {
			for (int c = 0; c < predicted_img.cols; ++c) {
				cv::Vec3b color = predicted_img.at<cv::Vec3b>(r, c);
				if (color[0] == 0) {
					predicted_img.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 0, 0);
				}
				else {
					predicted_img.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 255, 255);
				}
			}
		}

		char filename2[256];
		sprintf(filename2, (dlg.ui.lineEditOutputDirectory->text() + "/%02d_%06d_input.png").toUtf8().constData(), grammar_id, iter);
		cv::imwrite(filename2, img);

		char filename[256];
		sprintf(filename, (dlg.ui.lineEditOutputDirectory->text() + "/%02d_%06d_pred.png").toUtf8().constData(), grammar_id, iter);
		cv::imwrite(filename, predicted_img);

		iter++;
	}

	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Classification accuracy: " << (float)correct_classification / (correct_classification + incorrect_classification) << std::endl;
	std::cout << std::endl;

	// 誤差を計算
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Parameter estimation RMSE:" << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < rmse[i].size(); ++j) {
			if (j > 0) std::cout << ", ";
			rmse[i][j] =  sqrt(rmse[i][j] / rmse_count[i]);
			std::cout << rmse[i][j];
		}
		std::cout << std::endl;
	}
}


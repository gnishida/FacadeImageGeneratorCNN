#include "MainWindow.h"
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include "Classifier.h"
#include "Regression.h"
#include "Utils.h"
#include "facadeA.h"
#include "facadeB.h"
#include "facadeC.h"
#include "facadeD.h"

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
	//const string DATA_ROOT = "C:\\Anaconda\\caffe\\facade\\data\\images\\";
	const string DATA_ROOT = "C:/Anaconda/caffe/facade_regression/data/images/";
	const int NUM_IMAGES_PER_SNIPPET = 10000;
	const int IMAGE_SIZE = 128;
	const bool GRAYSCALE = true;

	boost::filesystem::path dir(DATA_ROOT);
	boost::filesystem::create_directory(dir);

	for (int facade_grammar_id = 0; facade_grammar_id < 4; ++facade_grammar_id) {
		srand(0);

		char dirname[256];
		sprintf(dirname, (DATA_ROOT + "%02d/").c_str(), facade_grammar_id + 1);
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
			//cv::Mat img = generateFacadeStructure(facade_grammar_id, IMAGE_SIZE, IMAGE_SIZE, params, false);
			cv::Mat img = generateFacadeStructure(facade_grammar_id, IMAGE_SIZE, IMAGE_SIZE, params, 2, false, 0, 1, 1, 0.0, 0.0);

			if (GRAYSCALE) {
				cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
			}

			///////////////////////////////////////////////////
			// save the image to the fiel
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

cv::Mat MainWindow::generateFacadeStructure(int facade_gramamr_id, int width, int height, std::vector<float>& params, int window_displacement, bool noise, int edge_displacement, float box_prob, float edge_prob, float noise_prob, float noise_length) {
	int thickness = 1;
	//int thickness = utils::uniform_rand(1, 4);

	cv::Mat result;
	if (facade_gramamr_id == 0) {
		result = generateFacadeA(width, height, thickness, params, window_displacement, noise, edge_displacement, box_prob, edge_prob);
	}
	else if (facade_gramamr_id == 1) {
		result = generateFacadeB(width, height, thickness, params, window_displacement, noise, edge_displacement, box_prob, edge_prob);
	}
	else if (facade_gramamr_id == 2) {
		result = generateFacadeC(width, height, thickness, params, window_displacement, noise, edge_displacement, box_prob, edge_prob);
	}
	else if (facade_gramamr_id == 3) {
		result = generateFacadeD(width, height, thickness, params, window_displacement, noise, edge_displacement, box_prob, edge_prob);
	}


	// 全体にノイズを追加する
	if (noise) {
		for (int i = 0; i < 100; ++i) {
			if (utils::uniform_rand() < noise_prob) {
				int c = utils::uniform_rand(0, width);
				int r = utils::uniform_rand(0, width);

				float len = utils::uniform_rand(1, noise_length);
				float theta = utils::uniform_rand(0, 3.141592653);
				int x1 = c - cosf(theta) * len * 0.5;
				int x2 = c + cosf(theta) * len * 0.5;
				int y1 = r - sinf(theta) * len * 0.5;
				int y2 = r + sinf(theta) * len * 0.5;
				cv::line(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), thickness);
			}
		}
	}

	return result;
}

void MainWindow::parameterEstimation() {
	const int N_TESTDATA = 1;

	boost::filesystem::path results_dir("results/");
	boost::filesystem::create_directory(results_dir);

#if 0
	Classifier classifier("C:/Anaconda/caffe/facade/model/deploy.prototxt", "C:/Anaconda/caffe/facade/model/train_iter_20000.caffemodel", "C:/Anaconda/caffe/facade/data/mean.binaryproto");
	std::vector<Regression*> regressions(4);
	for (int i = 0; i < 4; ++i) {
		char deploy_name[256];
		sprintf(deploy_name, "C:/Anaconda/caffe/facade_regression/model/deploy_%02d.prototxt", i + 1);
		char model_name[256];
		sprintf(model_name, "C:/Anaconda/caffe/facade_regression/model/train_%02d_iter_80000.caffemodel", i + 1);
		regressions[i] = new Regression(deploy_name, model_name);
	}
#endif
	
	for (int iter = 0; iter < N_TESTDATA; ++iter) {
		// テスト画像を作成する
		int grammar_snippet_id = utils::uniform_rand(0, 4);
		std::vector<float> params;
		cv::Mat img;
		if (grammar_snippet_id == 0) {
			img = generateFacadeA(256, 256, 1, params, 4, false);
		}
		else if (grammar_snippet_id == 1) {
			img = generateFacadeB(256, 256, 1, params, 4, false);
		}
		else if (grammar_snippet_id == 2) {
			img = generateFacadeC(256, 256, 1, params, 4, false);
		}
		else if (grammar_snippet_id == 3) {
			img = generateFacadeD(256, 256, 1, params, 4, false);
		}

		cv::imwrite("test.png", img);
#if 0

		std::vector<Prediction> predictions = classifier.Classify(img, 4);
		std::cout << "Predicted grammar id: #" << predictions[0].first + 1 << std::endl;


		// convert the image to grayscale with 128x128 size
		cv::Mat grayImg;
		cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
		cv::resize(grayImg, grayImg, cv::Size(128, 128));
		cv::threshold(grayImg, grayImg, 230, 255, cv::THRESH_BINARY);

		std::vector<float> predicted_params = regressions[predictions[0].first]->Predict(grayImg);

		cv::Mat predicted_img;
		if (predictions[0].first == 0) {
			predicted_img = generateFacadeA(256, 256, predicted_params);
		}
		else if (predictions[0].first == 1) {
			predicted_img = generateFacadeB(256, 256, predicted_params);
		}
		else if (predictions[0].first == 2) {
			predicted_img = generateFacadeC(256, 256, predicted_params);
		}
		else if (predictions[0].first == 3) {
			predicted_img = generateFacadeD(256, 256, predicted_params);
		}

		// blend the original image and the predicted one
		cv::Mat result(img.size(), CV_8UC3, cv::Scalar(255, 255, 255));
		for (int r = 0; r < predicted_img.rows; ++r) {
			for (int c = 0; c < predicted_img.cols; ++c) {
				cv::Vec3b orig_color = img.at<cv::Vec3b>(r, c);
				cv::Vec3b pred_color = predicted_img.at<cv::Vec3b>(r, c);
				if (pred_color[0] == 0) {
					result.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 0, 0);
				}
				else if (orig_color[0] == 0) {
					result.at<cv::Vec3b>(r, c) = cv::Vec3b(0, 0, 0);
				}
				else {
					result.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 255, 255);
				}
			}
		}

		char filename[256];
		sprintf(filename, "results/result_%02d.png", iter);
		cv::imwrite(filename, result);

#endif
	}
}
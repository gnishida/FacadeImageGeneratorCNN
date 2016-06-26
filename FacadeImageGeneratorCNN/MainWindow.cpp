#include "MainWindow.h"
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include "Classifier.h"
#include "Regression.h"
#include "Utils.h"
#include "ImageGenerationDialog.h"
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
	ImageGenerationDialog dlg;
	if (!dlg.exec()) return;

	//std::string DATA_ROOT = "//Lucy/caffe/facade/data/images/";
	//const string DATA_ROOT = "C:/Anaconda/caffe/facade_regression/data/images/";
	std::string DATA_ROOT = dlg.ui.lineEditOutputDirectory->text().toUtf8().constData();
	//int NUM_IMAGES_PER_SNIPPET = 10000;
	int NUM_IMAGES_PER_SNIPPET = dlg.ui.lineEditNumImages->text().toInt();
	//int IMAGE_SIZE = 128;// 227;
	int IMAGE_SIZE = dlg.ui.lineEditImageSize->text().toInt();
	//const bool GRAYSCALE = true;// false;
	bool GRAYSCALE = dlg.ui.checkBoxGrayscale->isChecked();

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
			//cv::Mat img = generateFacadeStructure(facade_grammar_id, IMAGE_SIZE, IMAGE_SIZE, params, 0, false, 0, 1, 1, 0.0, 0.0);
			cv::Mat img = generateFacadeStructure(facade_grammar_id, IMAGE_SIZE, IMAGE_SIZE, params, 2, 0.9);

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

cv::Mat MainWindow::generateFacadeStructure(int facade_gramamr_id, int width, int height, std::vector<float>& params, int window_displacement, float window_prob) {
	int thickness = 1;
	//int thickness = utils::uniform_rand(1, 4);

	cv::Mat result;
	if (facade_gramamr_id == 0) {
		result = generateRandomFacadeA(width, height, thickness, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 1) {
		result = generateRandomFacadeB(width, height, thickness, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 2) {
		result = generateRandomFacadeC(width, height, thickness, params, window_displacement, window_prob);
	}
	else if (facade_gramamr_id == 3) {
		result = generateRandomFacadeD(width, height, thickness, params, window_displacement, window_prob);
	}

	return result;
}

void MainWindow::parameterEstimation() {
	boost::filesystem::path results_dir("results/");
	boost::filesystem::create_directory(results_dir);

	Classifier classifier("C:/Anaconda/caffe/facade/model/deploy.prototxt", "C:/Anaconda/caffe/facade/model/train_iter_40000.caffemodel", "C:/Anaconda/caffe/facade/data/mean.binaryproto");
	std::vector<Regression*> regressions(4);
	for (int i = 0; i < 4; ++i) {
		char deploy_name[256];
		sprintf(deploy_name, "C:/Anaconda/caffe/facade_regression/model/deploy_%02d.prototxt", i + 1);
		char model_name[256];
		sprintf(model_name, "C:/Anaconda/caffe/facade_regression/model/train_%02d_iter_80000.caffemodel", i + 1);
		regressions[i] = new Regression(deploy_name, model_name);
	}

	int correct_classification = 0;
	int incorrect_classification = 0;

	std::ofstream out("predicted_params.txt");

	std::ifstream in("C:/Anaconda/caffe/facade/data/test.txt");
	int iter = 0;
	while (true) {
		std::string line;
		std::getline(in, line);
		int index = line.find(" ");
		if (index == std::string::npos) break;

		std::string file_path = line.substr(0, index);
		int grammar_id = std::stoi(line.substr(index + 1));

		cv::Mat img = cv::imread((std::string("C:/Anaconda/caffe/facade/data/images/") + file_path).c_str());
		//std::cout << file_path.c_str() << std::endl;

		// resize to 227x227
		//cv::Mat img = img240(cv::Rect(6, 6, 227, 227)).clone();
		/*
		cv::Mat img1 = img256(cv::Rect(0, 15, 227, 227)).clone();
		cv::Mat img2 = img256(cv::Rect(29, 15, 227, 227)).clone();
		cv::Mat img3 = img256(cv::Rect(15, 0, 227, 227)).clone();
		cv::Mat img4 = img256(cv::Rect(15, 29, 227, 227)).clone();
		*/

		// convert the image to grayscale with 128x128 size
		cv::Mat grayImg;
		cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
		cv::resize(grayImg, grayImg, cv::Size(128, 128));
		cv::threshold(grayImg, grayImg, 230, 255, cv::THRESH_BINARY);

		std::vector<Prediction> predictions = classifier.Classify(img, 4);
		/*
		std::vector<Prediction> predictions1 = classifier.Classify(img1, 4);
		std::vector<Prediction> predictions2 = classifier.Classify(img2, 4);
		std::vector<Prediction> predictions3 = classifier.Classify(img3, 4);
		std::vector<Prediction> predictions4 = classifier.Classify(img4, 4);
		std::cout << "   Predicted grammar id: #" << predictions[0].first + 1 << std::endl;
		std::cout << "                       : #" << predictions1[0].first + 1 << std::endl;
		std::cout << "                       : #" << predictions2[0].first + 1 << std::endl;
		std::cout << "                       : #" << predictions3[0].first + 1 << std::endl;
		std::cout << "                       : #" << predictions4[0].first + 1 << std::endl;
		*/

		if (predictions[0].first == grammar_id) correct_classification++;
		else incorrect_classification++;

		std::vector<float> predicted_params = regressions[predictions[0].first]->Predict(grayImg);
		for (int i = 0; i < predicted_params.size(); ++i) {
			if (i > 0) out << ",";
			out << predicted_params[i];
		}
		out << std::endl;

		// predictされた画像を作成する
		cv::Mat predicted_img;
		if (predictions[0].first == 0) {
			predicted_img = generateFacadeA(227, 227, 2, predicted_params);
		}
		else if (predictions[0].first == 1) {
			predicted_img = generateFacadeB(227, 227, 2, predicted_params);
		}
		else if (predictions[0].first == 2) {
			predicted_img = generateFacadeC(227, 227, 2, predicted_params);
		}
		else if (predictions[0].first == 3) {
			predicted_img = generateFacadeD(227, 227, 2, predicted_params);
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

		char filename2[256];
		sprintf(filename2, "results/test_%02d.png", iter);
		cv::imwrite(filename2, img);

		char filename[256];
		sprintf(filename, "results/result_%02d.png", iter);
		cv::imwrite(filename, result);

		iter++;

		//if (iter == 20) break;
	}

	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Prediction results:" << std::endl;
	std::cout << "Classification accuracy: " << (float)correct_classification / (correct_classification + incorrect_classification) << std::endl;
	std::cout << std::endl;
}

#if 0
void MainWindow::parameterEstimation() {
	const int N_TESTDATA = 200;

	boost::filesystem::path results_dir("results/");
	boost::filesystem::create_directory(results_dir);

	Classifier classifier("C:/Anaconda/caffe/facade/model/deploy.prototxt", "C:/Anaconda/caffe/facade/model/train_iter_40000.caffemodel", "C:/Anaconda/caffe/facade/data/mean.binaryproto");
	std::vector<Regression*> regressions(4);
	for (int i = 0; i < 4; ++i) {
		char deploy_name[256];
		sprintf(deploy_name, "C:/Anaconda/caffe/facade_regression/model/deploy_%02d.prototxt", i + 1);
		char model_name[256];
		sprintf(model_name, "C:/Anaconda/caffe/facade_regression/model/train_%02d_iter_80000.caffemodel", i + 1);
		regressions[i] = new Regression(deploy_name, model_name);
	}
	
	int correct_classification = 0;
	int incorrect_classification = 0;

	std::ofstream out("predicted_params.txt");
	for (int iter = 0; iter < N_TESTDATA; ++iter) {
		// テスト画像を作成する
		int grammar_snippet_id = utils::uniform_rand(0, 4);
		std::vector<float> params;
		cv::Mat img;
		if (grammar_snippet_id == 0) {
			img = generateRandomFacadeA(256, 256, 1, params, 2, 0.9);
		}
		else if (grammar_snippet_id == 1) {
			img = generateRandomFacadeB(256, 256, 1, params, 2, 0.9);
		}
		else if (grammar_snippet_id == 2) {
			img = generateRandomFacadeC(256, 256, 1, params, 2, 0.9);
		}
		else if (grammar_snippet_id == 3) {
			img = generateRandomFacadeD(256, 256, 1, params, 2, 0.9);
		}

		// convert the image to grayscale with 128x128 size
		cv::Mat grayImg;
		cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
		cv::resize(grayImg, grayImg, cv::Size(128, 128));
		cv::threshold(grayImg, grayImg, 230, 255, cv::THRESH_BINARY);

		std::vector<Prediction> predictions = classifier.Classify(img, 4);
		//std::cout << "Predicted grammar id: #" << predictions[0].first + 1 << std::endl;
		if (predictions[0].first == grammar_snippet_id) correct_classification++;
		else incorrect_classification++;

		std::vector<float> predicted_params = regressions[predictions[0].first]->Predict(grayImg);
		for (int i = 0; i < predicted_params.size(); ++i) {
			if (i > 0) out << ",";
			out << predicted_params[i];
		}
		out << std::endl;

		// predictされた画像を作成する
		cv::Mat predicted_img;
		if (predictions[0].first == 0) {
			predicted_img = generateFacadeA(256, 256, 2, predicted_params);
		}
		else if (predictions[0].first == 1) {
			predicted_img = generateFacadeB(256, 256, 2, predicted_params);
		}
		else if (predictions[0].first == 2) {
			predicted_img = generateFacadeC(256, 256, 2, predicted_params);
		}
		else if (predictions[0].first == 3) {
			predicted_img = generateFacadeD(256, 256, 2, predicted_params);
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

		char filename2[256];
		sprintf(filename2, "results/test_%02d.png", iter);
		cv::imwrite(filename2, img);

		char filename[256];
		sprintf(filename, "results/result_%02d.png", iter);
		cv::imwrite(filename, result);
	}

	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Prediction results:" << std::endl;
	std::cout << "Classification accuracy: " << (float)correct_classification / (correct_classification + incorrect_classification) << std::endl;
	std::cout << std::endl;
}

#endif
#include "Utils.h"
#include <math.h>
#include <random>

namespace utils {
	const float M_PI = 3.1415926535;

	double uniform_rand() {
		return (double)(rand() % 1000) / 1000.0;
	}

	double uniform_rand(double a, double b) {
		return uniform_rand() * (b - a) + a;
	}

	float gause(float u, float sigma) {
		return 1.0f / 2.0f / M_PI / sigma / sigma * expf(-u * u / 2.0f / sigma / sigma);
	}

	void drawLine(cv::Mat& img, cv::Point p1, cv::Point p2, float edge_prob, int noise_amount, const cv::Scalar& color, int thickness) {
		if (uniform_rand() < edge_prob) {
			cv::line(img, cv::Point(p1.x + uniform_rand(-noise_amount, noise_amount + 1), p1.y + uniform_rand(-noise_amount, noise_amount + 1)),
				cv::Point(p2.x + uniform_rand(-noise_amount, noise_amount + 1), p2.y + uniform_rand(-noise_amount, noise_amount + 1)), color, thickness);
		}
	}

	void drawRectangle(cv::Mat& img, cv::Point p1, cv::Point p2, float edge_prob, int noise_amount, const cv::Scalar& color, int thickness) {
		drawLine(img, p1, cv::Point(p2.x, p1.y), edge_prob, noise_amount, color, thickness);
		drawLine(img, cv::Point(p2.x, p1.y), p2, edge_prob, noise_amount, color, thickness);
		drawLine(img, p2, cv::Point(p1.x, p2.y), edge_prob, noise_amount, color, thickness);
		drawLine(img, cv::Point(p1.x, p2.y), p1, edge_prob, noise_amount, color, thickness);

		int noiseEdge = uniform_rand(0, 11);
		for (int i = 0; i < noiseEdge; ++i) {
			int x1 = uniform_rand(p1.x - 5, p2.x + 5);
			int y1 = uniform_rand(p1.y - 5, p2.y + 5);
			int x2 = uniform_rand(p1.x - 5, p2.x + 5);
			int y2 = uniform_rand(p1.y - 5, p2.y + 5);
			cv::line(img, cv::Point(x1, y1), cv::Point(x2, y2), color, thickness);
		}
	}

}
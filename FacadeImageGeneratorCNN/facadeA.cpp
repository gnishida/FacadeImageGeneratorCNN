#include "facadeA.h"
#include "Utils.h"

const int NF = 4;
const int NC = 4;

cv::Mat generateFacadeA(int width, int height, int thickness, const std::vector<float>& params) {
	float BS = (float)width / (params[5] * 2 + params[6] * NC) * params[5];
	float TW = (float)width / (params[5] * 2 + params[6] * NC) * params[6];
	float AH = (float)height / (params[7] + params[8] * NF + params[9]) * params[7];
	float FH = (float)height / (params[7] + params[8] * NF + params[9]) * params[8];
	float BH = (float)height / (params[7] + params[8] * NF + params[9]) * params[9];

	float WW = TW / (params[0] + params[2] * 2) * params[0];
	float WH = FH / (params[1] + params[3] + params[4]) * params[1];
	float WS = TW / (params[0] + params[2] * 2) * params[2];
	float WT = FH / (params[1] + params[3] + params[4]) * params[3];
	float WB = FH / (params[1] + params[3] + params[4]) * params[4];
	
	return generateFacadeA(width, height, thickness, WW, WH, WS, WT, WB, BS, TW, AH, FH, BH, 0, false);
}

cv::Mat generateFacadeA(int width, int height, int thickness, std::vector<float>& params, int window_displacement, bool noise, int edge_displacement, float window_prob, float edge_prob) {
	///////////////////////////////////////////////////////////////////////////////////
	// パラメータを設定
	float ratio;

	//int NF = 4;
	//int NC = 4;

	// ベースの高さ
	float BH = utils::uniform_rand(0, 0.5);

	// 屋根の高さ
	float AH = utils::uniform_rand(0, 0.5);

	// 各フロアの高さ
	float FH = utils::uniform_rand(2.5, 4);

	// 各タイルの幅
	float TW = utils::uniform_rand(2, 4);

	// ビルの横マージン
	float BS = utils::uniform_rand(0, 0.5);

	// 各フロアの窓上部から天井までの高さ
	float WT = utils::uniform_rand(0.2, 1);

	// 各フロアの窓下部からフロア底面までの高さ
	float WB = utils::uniform_rand(0.2, 1);

	// 各フロアの窓の高さ
	float WH = utils::uniform_rand(1, 2.5);

	// 各フロアの各種高さをnormalize
	ratio = FH / (WT + WB + WH);
	WT *= ratio;
	WB *= ratio;
	WH *= ratio;

	// 各フロアの窓の横マージン
	float WS = utils::uniform_rand(0.2, 1);

	// 各フロアの窓の幅
	float WW = utils::uniform_rand(0.5, 2.5);

	// 各フロアの各種幅をnormalize
	ratio = TW / (WS * 2 + WW);
	WS *= ratio;
	WW *= ratio;

	// すべてを画像のサイズにnormalize
	ratio = (float)height / (BH + AH + FH * NF);
	BH *= ratio;
	FH *= ratio;
	WT *= ratio;
	WB *= ratio;
	WH *= ratio;
	AH *= ratio;
	ratio = (float)width / (BS * 2 + TW * NC);
	BS *= ratio;
	WS *= ratio;
	WW *= ratio;
	TW *= ratio;

	///////////////////////////////////////////////////////////////////////////////////
	// パラメータ値を格納
	params.push_back(WW / TW);
	params.push_back(WH / FH);
	params.push_back(WS / TW);
	params.push_back(WT / FH);
	params.push_back(WB / FH);
	params.push_back(BS / width);
	params.push_back(TW / width);
	params.push_back(AH / height);
	params.push_back(FH / height);
	params.push_back(BH / height);

	return generateFacadeA(width, height, thickness, WW, WH, WS, WT, WB, BS, TW, AH, FH, BH, window_displacement, noise, edge_displacement, window_prob, edge_prob);
}

cv::Mat generateFacadeA(int width, int height, int thickness, float WW, float WH, float WS, float WT, float WB, float BS, float TW, float AH, float FH, float BH, int window_displacement, bool noise, int edge_displacement, float window_prob, float edge_prob) {
	cv::Mat result(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

	// 窓を描画
	for (int i = 0; i < NF; ++i) {
		for (int j = 0; j < NC; ++j) {
			int x1 = BS + TW * j + WS;
			int y1 = height - BH - FH * i - WB - WH;
			int x2 = BS + (WS * 2 + WW) * j + WS + WW;
			int y2 = height - BH - FH * i - WB;

			if (window_displacement > 0) {
				x1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				y1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				x2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				y2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
			}

			if (utils::uniform_rand() < window_prob) {
				if (!noise) {
					cv::rectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), thickness);
				}
				else {
					utils::drawRectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), edge_prob, edge_displacement, cv::Scalar(0, 0, 0), thickness);
				}
			}
		}
	}

	return result;
}
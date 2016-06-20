#include "facadeD.h"
#include "Utils.h"

const int NF = 4;
const int NC = 4;

cv::Mat generateFacadeD(int width, int height, const std::vector<float>& params) {
	float BS = (float)width / (params[5] * 2 + params[6] * NC) * params[5];
	float TW = (float)width / (params[5] * 2 + params[6] * NC) * params[6];
	float AH = (float)height / (params[7] + params[8] * (NF - 1) + params[9]) * params[7];
	float FH = (float)height / (params[7] + params[8] * (NF - 1) + params[9]) * params[8];
	float GH = (float)height / (params[7] + params[8] * (NF - 1) + params[9]) * params[9];

	float WW = TW / (params[0] + params[2] * 2) * params[0];
	float WH = FH / (params[1] + params[3] + params[4]) * params[1];
	float WS = TW / (params[0] + params[2] * 2) * params[2];
	float WT = FH / (params[1] + params[3] + params[4]) * params[3];
	float WB = FH / (params[1] + params[3] + params[4]) * params[4];

	int ND = params[10] * 2 + 1 + 0.5;
	if (ND == 0) ND = 1;
	if (ND > 3) ND = 3;
	float DT = GH / (params[11] + params[12]) * params[11];
	float DH = GH / (params[11] + params[12]) * params[12];
	float DW = TW * NC / ND / (params[13] + params[14] * 2) * params[13];
	float DS = TW * NC / ND / (params[13] + params[14] * 2) * params[14];

	return generateFacadeD(width, height, 1, WW, WH, WS, WT, WB, BS, TW, AH, FH, GH, ND, DT, DH, DW, DS, 0, false);
}

cv::Mat generateFacadeD(int width, int height, int thickness, std::vector<float>& params, int window_displacement, bool noise, int edge_displacement, float window_prob, float edge_prob) {
	///////////////////////////////////////////////////////////////////////////////////
	// パラメータを設定
	float ratio;

	int NF = 4;
	int NC = 4;

	// 屋根の高さ
	float AH = utils::uniform_rand(0, 0.5);

	// 各フロアの高さ
	float FH = utils::uniform_rand(2.5, 4);

	// １Fの高さ
	float GH = FH + utils::uniform_rand(0, 2);

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

	// １Fのドア上部から天井までの高さ
	float DT = utils::uniform_rand(0.2, 1.5);

	// １Fのドアの高さ
	float DH = utils::uniform_rand(2, 3);

	// １Fの各種高さをnormalize
	ratio = GH / (DT + DH);
	DT *= ratio;
	DH *= ratio;

	// １Fのドアの数（1 - 3）
	int ND = utils::uniform_rand(1, 4);

	// １Fのドアの横マージン
	float DS = utils::uniform_rand(0.2, 1);

	// １Fのドアの幅
	float DW = utils::uniform_rand(0.5, 4);

	// １Fの各種幅をnormalize
	ratio = TW * 2.0 / (DS * 2 + DW);
	DS *= ratio;
	DW *= ratio;

	// すべてを画像のサイズにnormalize
	ratio = (float)height / (GH + AH + FH * (NF - 1));
	GH *= ratio;
	FH *= ratio;
	WT *= ratio;
	WB *= ratio;
	WH *= ratio;
	AH *= ratio;
	DH *= ratio;
	DT *= ratio;
	ratio = (float)width / (BS * 2 + TW * NC);
	BS *= ratio;
	WS *= ratio;
	WW *= ratio;
	TW *= ratio;
	DS *= ratio;
	DW *= ratio;

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
	params.push_back(GH / height);
	params.push_back((float)(ND - 1) / 2.0f);
	params.push_back(DT / GH);
	params.push_back(DW / (DW + DS * 2));
	params.push_back(DS / (DW + DS * 2));

	return generateFacadeD(width, height, thickness, WW, WH, WS, WT, WB, BS, TW, AH, FH, GH, ND, DT, DH, DW, DS, window_displacement, noise, edge_displacement, window_prob, edge_prob);
}

cv::Mat generateFacadeD(int width, int height, int thickness, float WW, float WH, float WS, float WT, float WB, float BS, float TW, float AH, float FH, float GH, int ND, float DT, float DH, float DW, float DS, int window_displacement, bool noise, int edge_displacement, float window_prob, float edge_prob) {
	cv::Mat result(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

	// １Fのドアを描画
	for (int j = 0; j < NC / 2; ++j) {
		int x1 = BS + (DS * 2 + DW) * j + DS;
		int y1 = height - DH;
		int x2 = BS + (DS * 2 + DW) * j + DS + DW;
		int y2 = height - 1;

		if (window_displacement > 0) {
			x1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
			y1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
			x2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
			y2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
		}

		if (!noise) {
			cv::rectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), thickness);
		}
		else if (utils::uniform_rand() < window_prob) {
			utils::drawRectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), edge_prob, edge_displacement, cv::Scalar(0, 0, 0), thickness);
		}
	}

	// ２F以上の窓を描画
	for (int i = 0; i < NF - 1; ++i) {
		for (int j = 0; j < NC; ++j) {
			int x1 = BS + TW * j + WS;
			int y1 = height - GH - FH * i - WB - WH;
			int x2 = BS + (WS * 2 + WW) * j + WS + WW;
			int y2 = height - GH - FH * i - WB;

			if (window_displacement > 0) {
				x1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				y1 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				x2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
				y2 += utils::uniform_rand(-window_displacement, window_displacement + 1);
			}

			if (!noise) {
				cv::rectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), thickness);
			}
			else if (utils::uniform_rand() < window_prob) {
				utils::drawRectangle(result, cv::Point(x1, y1), cv::Point(x2, y2), edge_prob, edge_displacement, cv::Scalar(0, 0, 0), thickness);
			}

		}
	}

	return result;
}

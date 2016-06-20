#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat generateFacadeC(int width, int height, const std::vector<float>& params);
cv::Mat generateFacadeC(int width, int height, int thickness, std::vector<float>& params, int window_displacement, bool noise, int edge_displacement = 0, float window_prob = 1, float edge_prob = 1);
cv::Mat generateFacadeC(int width, int height, int thickness, float WW, float WH, float WS, float WT, float WB, float BS, float TW, float AH, float FH, float GH, int ND, float DT, float DH, float DW, float DS, int window_displacement, bool noise, int edge_displacement = 0, float window_prob = 1, float edge_prob = 1);

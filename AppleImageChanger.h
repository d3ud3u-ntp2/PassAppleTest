#pragma once
#include <opencv2/opencv.hpp>

// 入力画像 src を反転して dst に格納する。
// 成功すれば true、失敗（src.empty() 等）で false を返す。
bool AppleImageChanger(const cv::Mat& src, cv::Mat& dst);
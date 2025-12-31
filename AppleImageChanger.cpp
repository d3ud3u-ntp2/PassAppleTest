#include "AppleImageChanger.h"
#include <iostream>

bool AppleImageChanger(const cv::Mat& src, cv::Mat& dst)
{
    // fg: 合成する画像（apple_input）。src が与えられていればそれを使用、なければファイルから読み込む
    cv::Mat fg = src;
    if (fg.empty()) {
        fg = cv::imread("./resource_img/apple_input.jpg", cv::IMREAD_COLOR);
        if (fg.empty()) {_ソリューション エクスプローラー__でのテストプロジェクトの作り方や Google Test の導入手順
            std::cerr << "apple_input.jpg の読み込みに失敗しました。" << std::endl;
            return false;
        }
    }

    // bg: ベース画像（apple_before）をファイルから読み込む
    cv::Mat bg = cv::imread("./resource_img/apple_before.jpg", cv::IMREAD_COLOR);
    if (bg.empty()) {
        std::cerr << "apple_before.jpg の読み込みに失敗しました。" << std::endl;
        return false;
    }

    // 入力画像はカラー3チャンネルを期待する
    cv::Mat fgColor;
    if (fg.channels() == 1) {
        cv::cvtColor(fg, fgColor, cv::COLOR_GRAY2BGR);
    } else {
        fgColor = fg;
    }

    // サイズが bg より大きい場合は失敗（仕様上「同じ座標」に貼り付ける前提のため）
    if (fgColor.cols > bg.cols || fgColor.rows > bg.rows) {
        std::cerr << "エラー: 合成元画像がベース画像より大きいです。" << std::endl;
        return false;
    }

    // マスク作成: 黒字部分を透過（黒 = 0）、白地部分を貼り付けたい -> グレースケール化して閾値で白領域を抽出
    cv::Mat gray;
    cv::cvtColor(fgColor, gray, cv::COLOR_BGR2GRAY);
    cv::Mat mask;
    cv::threshold(gray, mask, 127, 255, cv::THRESH_BINARY); // 白っぽい部分が 255（貼り付け対象）

    // 貼り付け座標: 中央寄せ（画像が同サイズなら同じ位置）
    int offsetX = (bg.cols - fgColor.cols) / 2;
    int offsetY = (bg.rows - fgColor.rows) / 2;

    // ROI を取得してマスク付きコピー
    cv::Rect roiRect(offsetX, offsetY, fgColor.cols, fgColor.rows);
    cv::Mat roi = bg(roiRect);
    fgColor.copyTo(roi, mask); // mask の非ゼロ画素だけ roi にコピーされる

    dst = bg;
    return true;
}
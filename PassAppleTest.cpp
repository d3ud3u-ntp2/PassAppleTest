#include <iostream>
#include <opencv2/opencv.hpp>
#include "AppleImageChanger.h"

/*
■■■ 概要
- カラー画像を入力として受け取り、各ピクセルの色を反転させた画像を出力するプログラム
*/

int main()
{
    // カラーで読み込む（IMREAD_COLOR を使う）
    cv::Mat inputColor = cv::imread("./resource_img/apple_input.jpg", cv::IMREAD_COLOR);
    if (inputColor.empty()) {
        std::cerr << "apple_input.jpgの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // 反転処理を外部関数に委譲
    cv::Mat inverted;
    if (!AppleImageChanger(inputColor, inverted)) {
        std::cerr << "画像反転に失敗しました。" << std::endl;
        return 1;
    }

    // 反転結果を保存
    if (!cv::imwrite("./output_img/apple_after.png", inverted)) {
        std::cerr << "apple_after.pngの保存に失敗しました。" << std::endl;
        return 1;
    }

    std::cout << "apple_after.pngを保存しました。" << std::endl;
    return 0;
}
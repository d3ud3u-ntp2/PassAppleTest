#include <iostream>
#include <opencv2/opencv.hpp>

/*
■■■ 概要
- カラー画像を入力として受け取り、各ピクセルの色を反転させた画像を出力するプログラムを作成する。

*/

int main()
{
    // 入力画像（input.png）をカラーで読み込み
    cv::Mat inputColor = cv::imread("input.png", cv::IMREAD_COLOR);
    if (inputColor.empty()) {
        std::cerr << "input.pngの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    //// 画素反転処理（255 - ピクセル値）
    //cv::Mat inverted;
    //cv::bitwise_not(inputColor, inverted); // OpenCVのbitwise_notでカラー反転

    // 出力画像（apple_after.png）として保存
    if (!cv::imwrite("apple_after.png", inputColor)) {
    //if (!cv::imwrite("apple_after.png", inverted)) {
            std::cerr << "apple_after.pngの保存に失敗しました。" << std::endl;
        return 1;
    }

    std::cout << "apple_after.pngを保存しました。" << std::endl;
    return 0;
}
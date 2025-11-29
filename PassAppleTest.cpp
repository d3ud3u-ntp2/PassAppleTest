#include <iostream>
#include <opencv2/opencv.hpp>

/*
■■■ 概要
- カラー画像を入力として受け取り、各ピクセルの色を反転させた画像を出力するプログラム
*/

int main()
{
    // カラーで読み込む（IMREAD_COLOR を使う）
    cv::Mat inputColor = cv::imread("./resource_img/input.png", cv::IMREAD_COLOR);
    if (inputColor.empty()) {
        std::cerr << "input.pngの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // 確認（8bit 3チャンネルであること）
    if (inputColor.type() != CV_8UC3) {
        std::cerr << "警告: 期待する画像形式は CV_8UC3（8bit 3チャンネル）です。type=" << inputColor.type() << std::endl;
    }

    // 画素反転処理（各チャンネルごとに 255 - 値）
    cv::Mat inverted;
    cv::bitwise_not(inputColor, inverted); // 各チャンネルを反転する

    // 反転結果を保存（inverted を保存することに注意）
    if (!cv::imwrite("./output_img/apple_after.png", inverted)) {
        std::cerr << "apple_after.pngの保存に失敗しました。" << std::endl;
        return 1;
    }

    std::cout << "apple_after.pngを保存しました。" << std::endl;
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>

/*
■■■ 概要
- モノクロ画像を受け取り、同じ大きさの画素反転した画像を返すプログラム

■■■ 加工の概要
- モノクロ画像は0-255の値を持つピクセルの集合
- モノクロ画像はリソースファイルのinput.pngに置かれる
■■■ 入出力
- 入力: モノクロ画像（リソースファイルディレクトリのinput.png）
- 出力:リソースファイルディレクトリのapple_after.pngに保存される
■■■ 制約
- 画像の大きさは1x1から1000x1000まで
■■■ 例
- 入力:
    input.png
- 出力:
    apple_after.png
■■■ 注意事項
- 入力画像の形式やデータ型に注意すること
- 出力画像の形式やデータ型が入力画像と一致することを確認すること
- 処理速度やメモリ使用量に注意し、効率的なアルゴリズムを使用すること
- エッジケース（例: すべてのピクセルが0または255の場合）を考慮すること
 */

int main()
{
    // 入力画像（input.png）をグレースケールで読み込み
    cv::Mat inputGray = cv::imread("input.png", cv::IMREAD_GRAYSCALE);
    if (inputGray.empty()) {
        std::cerr << "input.pngの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // 画素反転処理（255 - ピクセル値）
    cv::Mat inverted;
    cv::bitwise_not(inputGray, inverted); // OpenCVのbitwise_notで画素反転

    // 出力画像（apple_after.png）として保存
    if (!cv::imwrite("apple_after.png", inverted)) {
        std::cerr << "apple_after.pngの保存に失敗しました。" << std::endl;
        return 1;
    }

    std::cout << "apple_after.pngを保存しました。" << std::endl;
    return 0;
}
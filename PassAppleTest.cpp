/*
■■■ 概要
- モノクロ画像を受け取り、加工し、同じ大きさの画像を返すプログラム

■■■ 加工の概要
- モノクロ画像は0-255の値を持つピクセルの集合
- モノクロ画像はリソースファイルのinput.pngに置かれる
- 画像の各ピクセルに対して、以下の操作を行う
- リソースファイルディレクトリのapple_before.png を赤みを強くして、モノクロ画像を中心に貼り付け、apple_after.png に保存する
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

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

 // 画像加工関数（モノクロ画像のピクセル値変換）
std::vector<std::vector<int>> processImage(const std::vector<std::vector<int>>& image) {
    size_t rows = image.size();
    size_t cols = rows ? image[0].size() : 0;
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            int pixel = image[i][j];
            if (pixel < 128) {
                pixel *= 2;
            }
            else {
                pixel = 255 - pixel;
            }
            if (pixel > 255) pixel = 255;
            if (pixel < 0) pixel = 0;
            result[i][j] = pixel;
        }
    }
    return result;
}

int main()
{
    // 入力画像（input.png）をグレースケールで読み込み
    cv::Mat inputGray = cv::imread("input.png", cv::IMREAD_GRAYSCALE);
    if (inputGray.empty()) {
        std::cerr << "input.pngの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // 2次元配列へ変換
    std::vector<std::vector<int>> image(inputGray.rows, std::vector<int>(inputGray.cols));
    for (int i = 0; i < inputGray.rows; ++i) {
        for (int j = 0; j < inputGray.cols; ++j) {
            image[i][j] = inputGray.at<uchar>(i, j);
        }
    }

    // ピクセル値加工
    std::vector<std::vector<int>> processed = processImage(image);

    // apple_before.pngをカラーで読み込み
    cv::Mat appleBefore = cv::imread("apple_before.png", cv::IMREAD_COLOR);
    if (appleBefore.empty()) {
        std::cerr << "apple_before.pngの読み込みに失敗しました。" << std::endl;
        return 1;
    }

    // 赤みを強くする
    cv::Mat appleRed = appleBefore.clone();
    for (int y = 0; y < appleRed.rows; ++y) {
        for (int x = 0; x < appleRed.cols; ++x) {
            cv::Vec3b& pixel = appleRed.at<cv::Vec3b>(y, x);
            pixel[2] = std::min(255, pixel[2] + 80); // R成分を強調
        }
    }

    // モノクロ画像を中心に貼り付け
    int offsetY = (appleRed.rows - inputGray.rows) / 2;
    int offsetX = (appleRed.cols - inputGray.cols) / 2;
    for (int i = 0; i < inputGray.rows; ++i) {
        for (int j = 0; j < inputGray.cols; ++j) {
            int val = processed[i][j];
            cv::Vec3b monoPixel(val, val, val);
            appleRed.at<cv::Vec3b>(offsetY + i, offsetX + j) = monoPixel;
        }
    }

    // 加工後画像を保存
    if (!cv::imwrite("apple_after.png", appleRed)) {
        std::cerr << "apple_after.pngの保存に失敗しました。" << std::endl;
        return 1;
    }

    std::cout << "apple_after.pngを保存しました。" << std::endl;
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します

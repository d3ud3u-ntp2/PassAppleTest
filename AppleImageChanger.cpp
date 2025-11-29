#include "AppleImageChanger.h"

bool AppleImageChanger(const cv::Mat& src, cv::Mat& dst)
{
    if (src.empty()) return false;

    // 出力は入力と同じサイズ・型になるようにする（必要に応じて8ビットへ変換）
    cv::Mat tmp;
    if (src.depth() != CV_8U) {
        // 浮動小数点などが来た場合は 8bit に変換（値域は暗黙にクリップ/スケールしない）
        src.convertTo(tmp, CV_8U);
    } else {
        tmp = src;
    }

    // 各チャンネルごとにビット反転（255 - pixel）を行う
    cv::bitwise_not(tmp, dst);
    return true;
}
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

// ファイル
#define FILE_NAME "../issue1.jpg"
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

// 二値化閾値
#define BIN_TH (100)

int main(int argc, const char *argv[])
{
    // 1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    // 2. 輪郭の座標リストの宣言
    std::vector<std::vector<cv::Point>>
        contours;

    // 3. 画像の入力 (カラーで入力)
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty())
    { // 入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    // 4. 入力画像を結果画像にコピー
    dst_img = src_img.clone();

    // 5. グレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    // 6. 二値化 (固定閾値で実装．閾値: 100)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

    // 二値画像コピー
    tmp_img = bin_img.clone();

    // 7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // 8. 円形度を計算して、円だけを除外
    for (int i = 0; i < contours.size(); i++)
    {
        // 輪郭の周囲長を計算
        double len = cv::arcLength(contours[i], true);

        // 輪郭の面積を計算
        double area = cv::contourArea(contours[i]);

        // 円形度を計算
        double circularity = (4 * M_PI * area) / (len * len);

        // 円形度が0.8以上の輪郭は円とみなす
        if (circularity > 0.8)
        {
            // 輪郭の内部を黒く塗りつぶす
            cv::drawContours(bin_img, contours, i, cv::Scalar(0), -1);
        }
    }

    cv::Mat bin_copy_img = bin_img.clone();

    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1, -1), 20);

    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1, -1), 20);

    // 9. bin_imgの輪郭抽出
    cv::findContours(bin_img, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // 10. 図形全体を塗りつぶし
    dst_img = cv::Mat(src_img.size(), CV_8UC3);
    cv::Scalar color[] = {
        CV_RGB(255, 0, 255),
        CV_RGB(255, 0, 0)};

    for (int i = 0; i < contours.size(); i++)
    {
        cv::drawContours(dst_img, contours, i, color[i % 2], -1);
    }

    // 11. 図形のうちbin_copy_imageの黒い場所を塗りつぶし
    for (int y = 0; y < src_img.rows; y++) {
        for (int x = 0; x < src_img.cols; x++) {
            if (bin_copy_img.at<uchar>(y, x) == 0) {
                dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
            }
        }
    }


    // 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

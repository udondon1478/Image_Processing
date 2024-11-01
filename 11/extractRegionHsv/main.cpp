//
//  extractRegion.cpp
//
//
//  Created by Masashi Morimoto on 2023/06/20.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../fruit_image.jpg"

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define H_MIN (50)        // Hのしきい値
#define H_MAX (200)        // Hのしきい値
#define V_MAX (195)        // Vのしきい値
#define WHITE_PIXEL (255) // 出力画像の値（白）

int main(int argc, const char *argv[])
{
    // 変数の宣言
    int x, y;    // 走査用
    cv::Vec3b p; // 色値

    // 画像の宣言 (入力画像，出力画像)
    cv::Mat src_img, dst_img;

    // 1. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty())
    { // 入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 3. しきい値処理
    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++)
        {
            // H(色相) : 大きい値
            // V(明度) : やや小さい値
            //HSV色空間に変換
            cv::Mat hsv_img;
            cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

            // 画素値を取得
            p = hsv_img.at<cv::Vec3b>(y, x);

            // Hのしきい値処理
            if (p[0] > H_MIN && p[0] < H_MAX)
            {
                // Vのしきい値処理
                if (p[2] < V_MAX)
                {
                    // 出力画像の画素値を白にする
                    dst_img.at<unsigned char>(y, x) = WHITE_PIXEL;
                }
            }

        }
    }

    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);  // 入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey();                           // キー入力待ち (止める)

    return 0;
}

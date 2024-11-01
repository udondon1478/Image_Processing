#include <opencv2/opencv.hpp>
#include <iostream>

#define FILE_NAME "../input3.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define H_MIN (70)
#define H_MAX (100)
#define S_MIN (35)
#define V_MIN (50)

#define BLACK_PIXEL (0, 0, 0)

int main(int argc, const char **argv)
{

    // 変数の宣言
    int x, y;    // 走査用
    cv::Vec3b p; // 色値
    int h, s, v;

    // 画像用の変数の宣言
    cv::Mat src_img, dst_img, hsv_img;
    // 画像入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty())
    {
        std::cerr << "入力画像が見つかりません" << std::endl;
        return -1;
    }

    // 2. 出力二値画像の領域を確保
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 3. RGBからHSVへ変換
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    // 4. 閾値処理
    for (y = 0; y < hsv_img.rows; y++)
    {
        for (x = 0; x < hsv_img.cols; x++)
        {
            p = hsv_img.at<cv::Vec3b>(y, x);
            h = p[0];
            s = p[1];
            v = p[2];
            if (h > H_MIN && h < H_MAX)
            {
                hsv_img.at<cv::Vec3b>(y, x) = BLACK_PIXEL;
            }
            if (s < S_MIN)
            {
                hsv_img.at<cv::Vec3b>(y, x) = BLACK_PIXEL;
            }
            if (v < V_MIN)
            {
                hsv_img.at<cv::Vec3b>(y, x) = BLACK_PIXEL;
            }
        }
    }

    // 5. HSVをRGBに変換
    cv::cvtColor(hsv_img, dst_img, cv::COLOR_HSV2BGR);

    // 6. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img); // 入力画像の表示
    cv::imshow("hsv", hsv_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey();                           // キー入力待ち (止める)

    return 0;
}
// Github Copilotを使用
// プロンプト未入力

//7月31日 14:16 x22001 青嶋瑠捺とx22052 島崎流奈に相談を受け、回答しました。
#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../fruit_image.jpg"

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define WHITE_PIXEL (0)
#define BIN_TH (100)

int main(int argc, const char *argv[])
{
    // 変数の宣言
    int x, y;
    cv::Vec3b p;
    int h, s, v;

    // 画像の宣言
    cv::Mat src_img, dst_img, hsv_img, bin_img, gray_img;

    std::vector<std::vector<cv::Point>> contours;

    // 1. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty())
    {
        std::cout << "File not found" << std::endl;
        return -1;
    }

    // 2. 出力画像の領域確保
    dst_img = src_img.clone();

    // 3. HSV画像への変換
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    // 4. 色相(Hue)を用いて赤りんごの領域を判定
    for (y = 0; y < hsv_img.rows; y++)
    {
        for (x = 0; x < hsv_img.cols; x++)
        {
            p = hsv_img.at<cv::Vec3b>(y, x);
            h = p[0];
            s = p[1];
            v = p[2];
            if (h > 100 || h < 30 || s < 50 || v < 80)
            {
                hsv_img.at<cv::Vec3b>(y, x) = WHITE_PIXEL;
            }
        }
    }

    // 5. 二値化
    cv::cvtColor(hsv_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

    // 6. 輪郭抽出
    cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // 7. 面積が小さい輪郭を塗りつぶす
    for (int i = 0; i < contours.size(); i++)
    {
        double S = cv::contourArea(contours[i]); // 面積
        if (S <= 5000)
        {
            cv::drawContours(bin_img, contours, i, 0, -1);
        }
    }

    // 8. 青リンゴの領域を緑色で塗りつぶす
    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            if (bin_img.at<uchar>(y, x) == 255)
            {
                dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 255, 0);
            }
        }
    }

    // 9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img); // 入力画像の表示
    cv::imshow("hsv", hsv_img);
    cv::imshow("gray", gray_img);
    cv::imshow("bin", bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey();                           // キー入力待ち (止める)

    return 0;
}

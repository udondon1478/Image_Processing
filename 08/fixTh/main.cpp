#include <iostream>
#include <opencv2/opencv.hpp>

#define HIGHVAL (255)
#define LOWVAL (0)
#define TH (100)
#define FILE_NAME "../red_rectangle.jpg"

#define WINDOW_NAME_INPUT "Input"
#define WINDOW_NAME_OUTPUT "Output"
#define WINDOW_NAME_GRAY "Gray"

int main(int argc, char const *argv[])
{
    // 変数定義
    cv::Mat src_img, gray_img, bin_img;
    // 画像入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    // 画像の読み込みに失敗したらエラー終了
    if (src_img.empty())
    {
        std::cerr << "File not found" << std::endl;
        return -1;
    }
    // 輝度画像への変換
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    // 二値画像の生成
    bin_img.create(gray_img.size(), gray_img.type());

    // 二値画像への変換
    for (int y = 0; y < gray_img.rows; y++)
    {
        for (int x = 0; x < gray_img.cols; x++)
        {
            if (gray_img.at<unsigned char>(y, x) > TH)
            {
                bin_img.at<unsigned char>(y, x) = HIGHVAL;
            }
            else
            {
                bin_img.at<unsigned char>(y, x) = LOWVAL;
            }
        }
    }

    // 画像の表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, bin_img);
    cv::imshow(WINDOW_NAME_GRAY, gray_img);

    return 0;
}

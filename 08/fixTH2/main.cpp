#include <iostream>
#include <opencv2/opencv.hpp>

#define HIGHVAL (255)
#define LOWVAL (0)
#define TH (100)
#define FILE_NAME "../red_rectangle.jpg"

#define WINDOW_NAME_INPUT "Input"
#define WINDOW_NAME_BIN "Bin"
#define WINDOW_NAME_GRAY "Gray"

int main(int argc, char const *argv[])
{
    //画像をグレースケールで入力
    cv::Mat gray_img, bin_img;
    gray_img = cv::imread(FILE_NAME, 0);
    if (gray_img.empty())
    {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }

    // 画像の二値化
    cv::threshold(gray_img, bin_img, TH, HIGHVAL, cv::THRESH_BINARY_INV);
    // 画像の表示
    cv::imshow(WINDOW_NAME_BIN, bin_img);
    cv::imshow(WINDOW_NAME_GRAY, gray_img);
    cv::waitKey();
    return 0;
}

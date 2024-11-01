#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "../gazoDora.jpg"
#define TEMPLATE_IMG_RED "../red.jpg"

#define WINDOW_INPUT "Input Image"
#define WINDOW_OUTPUT "Output Image"

int main(void)
{
    // 画像の読み込み
    cv::Mat src_img = cv::imread(TARGET_IMG_FILE, 0);
    cv::Mat template_red_img = cv::imread(TEMPLATE_IMG_RED, 0);

    // 画像の読み込みに失敗した場合
    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");

        return (-1);
    }

    cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_red_img.rows + 1, src_img.cols - template_red_img.cols + 1), CV_32F);
    cv::matchTemplate(src_img, template_red_img, compare_img, cv::TM_SQDIFF_NORMED);

    // 正規化
    cv::Mat dst_img = cv::Mat(compare_img.size(), CV_8UC1);
    for (int y = 0; y < compare_img.rows; y++)
    {
        for (int x = 0; x < compare_img.cols; x++)
        {
            dst_img.at<uchar>(y, x) = compare_img.at<float>(y, x) * 255;
        }
    }

    // 画像の表示
    cv::imshow("dst_img", dst_img);
    cv::waitKey();

    return 0;
}
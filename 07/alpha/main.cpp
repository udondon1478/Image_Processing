#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../input1.jpg"
#define FILE_NAME2 "../input2.jpg"
#define ALPHA (0.3)

#define WINDOW_NAME_INPUT1 "Input1"
#define WINDOW_NAME_INPUT2 "Input2"
#define WINDOW_NAME_OUTPUT "Output"

int main(int argc, char const *argv[])
{
    //画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME, 0); //画像1
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0); //画像2
    if (src_img1.empty() || src_img2.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    cv::Mat result_img = cv::Mat (src_img1.size(), CV_8UC1); //合成画像))
    int x, y;

    //合成画像の出力
    for (y = 0; y < src_img1.rows; y++)
    {
        for (x = 0; x < src_img1.cols; x++)
        {
            //画素値の取得
            double s1 = (double)src_img1.at<unsigned char>(y, x);
            double s2 = (double)src_img2.at<unsigned char>(y, x);
            int s_result = ALPHA * s1 + (1.0 - ALPHA) * s2;
            result_img.at<unsigned char>(y, x) = (unsigned char)s_result;
        }
    }

    ///画像の表示
    cv::imshow(WINDOW_NAME_INPUT1, src_img1);
    cv::imshow(WINDOW_NAME_INPUT2, src_img2);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey(0);
    return 0;
}

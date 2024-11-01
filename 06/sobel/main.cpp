#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale (1).jpg"

int main(int argc, char const *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);

    if (src_img.empty())
    {
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    cv::Mat dst_img;
    cv::Mat tmp_img;

    cv::Sobel(src_img, tmp_img, CV_32F, 1, 0);

    // 微分フィルタをtmp_imgにかける
    cv::convertScaleAbs(tmp_img, dst_img, 1, 0);



    // 画像の表示
    cv::imshow("src", src_img);
    cv::imshow("dst", dst_img);
    cv::waitKey(0);

    return 0;
}

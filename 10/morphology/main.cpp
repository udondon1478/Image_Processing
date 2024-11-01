#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../a_img.jpg"

#define THRESHOLD 100

#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[])
{
int i;

    //グレースケールで画像を入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    //入力画像の二値化
    cv::Mat bin_img;
    cv::threshold(src_img, bin_img, THRESHOLD, 255, cv::THRESH_BINARY);

    //画像の膨張(10回)

    cv::Mat dst_img;
    cv::Mat dilate;
    cv::Mat erode;
    for (i = 0; i < 8; i++)
    {
        cv::dilate(bin_img, dilate, cv::Mat(), cv::Point(-1, -1), i);
        cv::imshow(WINDOW_NAME_OUTPUT, dilate);

        cv::erode(dilate, dst_img, cv::Mat(), cv::Point(-1, -1), i);
        cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
        cv::waitKey(0);
        if (i == 7)
        {
            int j;
            for (j = 0; j < 16; j++)
            {
                cv::erode(dst_img, erode, cv::Mat(), cv::Point(-1, -1), j);
                cv::imshow(WINDOW_NAME_OUTPUT, erode);
                cv::waitKey(0);
            }
        }
        
    }
    
    //画像の表示
    cv::imshow("src", src_img);
    cv::imshow("dst", dst_img);
    cv::waitKey(0);


    return 0;
}

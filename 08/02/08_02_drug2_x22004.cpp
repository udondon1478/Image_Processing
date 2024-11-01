#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../sample.png"
#define FILE_NAME2 "../drug11.png"

#define HIGHVAL 255
#define LOWVAL 0

#define ERROR_RANGE 3

int main(int argc, char const *argv[])
{
    // 画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, 1);
    cv::Mat gray_img;

    if (src_img.empty())
    {
        std::cout << "Can't open image." << std::endl;
        return -1;
    }

    // RGBの各色が何回出るかを判定
    int num_R[256] = {0}, num_G[256] = {0}, num_B[256] = {0};

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            if (bgr[0] != 0 && bgr[1] != 0 && bgr[2] != 0)
            {
                num_B[bgr[0]]++;
                num_G[bgr[1]]++;
                num_R[bgr[2]]++;
            }
        }
    }

    // RGBの最大値と最頻値を取得
    int maxR = 0, maxG = 0, maxB = 0;
    int freqRValue = 0, freqGValue = 0, freqBValue = 0;

    for (int i = 0; i < 256; i++)
    {
        if (num_R[i] > maxR)
        {
            maxR = num_R[i];
            freqRValue = i;
        }
        if (num_G[i] > maxG)
        {
            maxG = num_G[i];
            freqGValue = i;
        }
        if (num_B[i] > maxB)
        {
            maxB = num_B[i];
            freqBValue = i;
        }
    }

    // image2をsrc_imgに上書き読み込み
    src_img = cv::imread(FILE_NAME2, 1);

    if (src_img.empty())
    {
        std::cout << "Can't open image." << std::endl;
        return -1;
    }

    // メモリ確保
    gray_img.create(src_img.size(), CV_8UC1);

    // freqValueを元に二値化
    int j = 0, k = 0;
    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            cv::Vec3b bgr = src_img.at<cv::Vec3b>(y, x);
            if (
                bgr[0] > (freqBValue - ERROR_RANGE) && bgr[0] < (freqBValue + ERROR_RANGE) &&
                bgr[1] > (freqGValue - ERROR_RANGE) && bgr[1] < (freqGValue + ERROR_RANGE) &&
                bgr[2] > (freqRValue - ERROR_RANGE) && bgr[2] < (freqRValue + ERROR_RANGE))
            {
                gray_img.at<unsigned char>(y, x) = HIGHVAL;
                j++;
            }
            else
            {
                gray_img.at<unsigned char>(y, x) = LOWVAL;
                k++;
            }
        }
    }

    // 結果計算及び表示
    float rate = (float)j / (j + k);
    if (rate < 0.17)
        printf("欠損\n");
    else if (rate > 0.23)
        printf("膨張\n");
    else
        printf("正常\n");

    return 0;
}
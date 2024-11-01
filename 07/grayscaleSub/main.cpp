#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME1 "../input1.jpg"
#define FILE_NAME2 "../input2.jpg"
#define THRESHOLD (20)  //閾値

//ウィンドウ名
#define WINDOW_NAME1 "input1"
#define WINDOW_NAME2 "input2"
#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[])
{
    //画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);   //画像1
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);   //画像2
    if (src_img1.empty() || src_img2.empty())
    {
        std::cout << "画像が読み込めませんでした．" << std::endl;
        return -1;
    } 
    
    cv::Mat sub_img = cv::Mat(src_img1.size(), CV_8UC1); //差分画像))
    cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1); //結果画像(二値)
    int x, y;

    //差分の出力
    for (y = 0; y < src_img1.rows; y++)
    {
        for (x = 0; x < src_img1.cols; x++)
        {
            //画素値の取得(int型)
            int s1 = (int)src_img1.at<unsigned char>(y, x);
            int s2 = (int)src_img2.at<unsigned char>(y, x);
            int s_result = abs(s1 - s2);    //差分の絶対値
            sub_img.at<unsigned char>(y, x) = (unsigned char)s_result; //差分画像の出力

            if (s_result > THRESHOLD) //閾値処理
            {
                s_result = 255;
            }else {
                s_result = 0;
            }
        }
    }

    //結果画像の出力
    cv::imshow(WINDOW_NAME1, src_img1);
    cv::imshow(WINDOW_NAME2, src_img2);
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    return 0;
}

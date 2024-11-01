#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../guide_valor_logo_A.png"

#define WINDOW_NAME_INPUT "Input"
#define WINDOW_NAME_OUTPUT_H "Output_H"
#define WINDOW_NAME_OUTPUT_V "Output_V"
#define WINdOW_NAME_OUTPUT_G "Output_G"

int main(int argc, char const *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 1);

    if (src_img.empty())
    {
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    cv::Mat dst_img, H_img, G_img, V_img, tmp_img;

    cv::cvtColor(src_img, tmp_img, cv::COLOR_BGR2GRAY);

    // G_imgのメモリ確保
    G_img = cv::Mat(src_img.size(), CV_64FC1);

    // ソーベルフィルタ出力(横)を求める
    cv::Sobel(tmp_img, H_img, CV_64FC1, 1, 0);

    // ソーベルフィルタ出力(縦)を求める
    cv::Sobel(tmp_img, V_img, CV_64FC1, 0, 1);

    // 勾配を用いてH_imgとV_imgを合成する
    for (int y = 0; y < tmp_img.rows; y++)
    {
        for (int x = 0; x < tmp_img.cols; x++)
        {
            // H_imgとV_imgの勾配を求める
            double H = H_img.at<double>(y, x);
            double V = V_img.at<double>(y, x);

            // 勾配を求める
            double G = sqrt(H * H + V * V);

            // G_imgに代入
            G_img.at<double>(y, x) = G;
        }
    }

    cv::convertScaleAbs(G_img, G_img);

    // 画像を出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_H, H_img);
    cv::imshow(WINDOW_NAME_OUTPUT_V, V_img);
    cv::imshow(WINdOW_NAME_OUTPUT_G, G_img);
    cv::waitKey(0);

    return 0;
}

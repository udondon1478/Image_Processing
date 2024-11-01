#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_tree.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT_GAUSSIAN "output_gaussian"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, char const *argv[])
{
    // カラー画像を入力
    cv::Mat src_img = cv::imread(FILE_NAME, 1);

    if (src_img.empty())
    {
        std::cout << "画像が読み込めませんでした．" << std::endl;
        return -1;
    }

    // 出力画像と仮画像の宣言
    cv::Mat dst_img, tmp_img;

    // src_imgをグレースケール画像に変換
    cv::cvtColor(src_img, tmp_img, cv::COLOR_BGR2GRAY);

    // ガウシアンフィルタを適用
    cv::GaussianBlur(tmp_img, tmp_img, cv::Size(FILTER_SIZE, FILTER_SIZE), 0);

    // ソーベルフィルタを適応
    cv::Sobel(tmp_img, dst_img, CV_32F, 0, 1);


    // 適切な出力画像に変換
    
    cv::convertScaleAbs(dst_img, dst_img);

    // 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT_GAUSSIAN, tmp_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(0);

    return 0;
}

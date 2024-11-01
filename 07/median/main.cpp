#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define FILTER_SIZE (5) //フィルタサイズ(3以上の奇数)

int main(int argc, char const *argv[])
{
    //画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty())
    {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    
    cv::Mat median_img; //出力画像の宣言
    //メディアンフィルタ(入力,出力,フィルタサイズ)
    cv::medianBlur(src_img, median_img, FILTER_SIZE);
    //表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, median_img);
    cv::waitKey(0);
    return 0;
}

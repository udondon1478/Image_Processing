#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, char const *argv[])
{
    //1. グレースケールで画像を読み込む
    cv::Mat src_img = cv::imread(FILE_NAME, 0);

    if (src_img.empty())
    {
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }
    
    //2. 出力画像の宣言(処理4で自動的にメモリ確保される)
    cv::Mat dst_img;

    //3. ガウシアンフィルタの宣言と設計
    cv::GaussianBlur(src_img, dst_img, cv::Size(FILTER_SIZE, FILTER_SIZE), 0);
    //4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(0);
    return 0;
}



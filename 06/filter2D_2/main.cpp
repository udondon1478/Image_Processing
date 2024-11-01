#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../apple_grayscale.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

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

    //3. フィルタの宣言と設計(入力と正規化)
    double filter_h[] = {-1., 0., 1.,
                         -2., 0., 2.,
                         -1., 0., 1.};
    //配列をフィルタ行列kernelに変換
    cv::Mat kernel(3, 3, CV_64F, filter_h);
    //正規化
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //4. フィルタの計算
    //  cv::filter2D(src_img, dst_img, -1, kernel);
    cv::Mat tmp_img;    //一時的な画像
    cv::filter2D(src_img, tmp_img, CV_64F, kernel);
    cv::convertScaleAbs(tmp_img, dst_img);
    //5. 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(0);
    return 0;
}



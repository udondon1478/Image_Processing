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
    cv::Mat dst_img2;
    //3. フィルタの宣言と設計(入力と正規化)
    double filter_h[] = {1/16., 2/16., 1/16.,
                         2/16., 4/16., 2/16.,
                         1/16., 2/16., 1/16.};
    //ガウシアンフィルタ


    //3.5 5x5の一様平均化フィルタの宣言と設計

    double filter_h2[] = {1/25., 1/25., 1/25., 1/25., 1/25.,
                            1/25., 1/25., 1/25., 1/25., 1/25.,
                            1/25., 1/25., 1/25., 1/25., 1/25.,
                            1/25., 1/25., 1/25., 1/25., 1/25.,
                            1/25., 1/25., 1/25., 1/25., 1/25., 
    };

    //配列をフィルタ行列kernelに変換
    cv::Mat kernel(3, 3, CV_32F, filter_h);
    cv::Mat kernel2(5, 5, CV_32F, filter_h2);
    //正規化
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    cv::normalize(kernel2, kernel2, 1.0, 0.0, cv::NORM_L1);
    //4. フィルタの計算
    cv::filter2D(src_img, dst_img, -1, kernel);
    cv::filter2D(src_img, dst_img2, -1, kernel2);
    //5. 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::imshow("5x5", dst_img2);
    cv::waitKey(0);
    return 0;
}



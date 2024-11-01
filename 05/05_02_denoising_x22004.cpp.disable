#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../kanji.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (8)

int main(int argc, char const *argv[])
{
    // 回数用変数
    int i = 0;
    int x, y;

    unsigned char Imin, Imax, Dmin, Dmax;

    // 1. グレースケールで画像を読み込む
    cv::Mat src_img = cv::imread(FILE_NAME, 0);

    if (src_img.empty())
    {
        std::cout << "画像が読み込めませんでした" << std::endl;
        return -1;
    }

    // 2. 出力画像の宣言
    cv::Mat dst_img;
    cv::Mat dst_img_clone;

    // 初期値の入力(Imin, Imax)
    Imax = 0;
    Imin = 255;

    // 変換後の画素値の入力
    Dmin = 255;
    Dmax = 0;

    // 3. 平均化フィルタをn回適応する

    cv::blur(src_img, dst_img, cv::Size(FILTER_SIZE, FILTER_SIZE));

    dst_img_clone = dst_img;

    for (y = 0; y < dst_img_clone.rows; y++)
    {
        for (x = 0; x < dst_img_clone.cols; x++)
        {
            // 5. 変換
            if (dst_img_clone.at<unsigned char>(y, x) < 150)
            {
                dst_img.at<unsigned char>(y, x) = Dmax;
            }
            else if (dst_img_clone.at<unsigned char>(y, x) > 0)
            {
                dst_img.at<unsigned char>(y, x) = Dmin;
            }
        }
    }

    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(0);
    return 0;
}

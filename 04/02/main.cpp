#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "/Users/x22004xx/src/imgProc/第4回/02/image2.jpg"
#define COLOR_MAX (256)

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

/*
int main(int argc, char const *argv[])
{
    // 1. 変数の宣言
    int x, y;
    int count = 0;

    // 変換前の画素値の最小値・最大値、変換後の画素値の最小値・最大値
    unsigned char Imin, Imax, Dmin, Dmax;

    // 2. 初期値の入力(Imin, Imax)
    Imax = 0;
    Imin = 255;

    // 変換後の画素値の入力
    Dmin = 0;
    Dmax = 255;

    // 3. 画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty())
    {
        fprintf(stderr, "FIle is not opened\n");
        return (-1);
    }

    // 4. 出力画像のメモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++)
        {
            // 5. 変換
            if (src_img.at<unsigned char>(y, x) < 121)
            {
                count++;
            }

            if (src_img.at<unsigned char>(y, x) < 121)
            {
                dst_img.at<unsigned char>(y, x) = Dmax;
            }
            else if (src_img.at<unsigned char>(y, x) > 0)
            {
                dst_img.at<unsigned char>(y, x) = Dmin;
            }
        }
    }

    // ヒストグラム用配列出力用プログラム
    //  1. 変数の宣言
    int i; // アクセス用の変数

    int hist[COLOR_MAX]; // ヒストグラム用の配列

    // 2. ヒストグラム用配列の初期化
    for (i = 0; i < COLOR_MAX; i++)
    {
        hist[i] = 0;
    }

    // 3. ヒストグラムの生成
    for (y = 0; y < dst_img.rows; y++)
    {
        for (x = 0; x < dst_img.cols; x++)
        {
            // 画素値の取得
            unsigned char s = dst_img.at<unsigned char>(y, x);
            hist[(int)s]++; // 画素値の計算
        }
    }

    // 4. 出力(Numbers or Excel用に印字)
    for (i = 0; i < COLOR_MAX; i++)
    {
        printf("%d %d\n", i, hist[i]);
    }

    printf("%d\n", count);
    return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "/Users/x22004xx/src/imgProc/第4回/02/image2.jpg"
*/

int main(int argc, char const *argv[])
{
    // 1. 変数の宣言
    int x, y;
    int count = 0;

    // 3. 画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty())
    {
        fprintf(stderr, "FIle is not opened\n");
        return (-1);
    }

    // 4. 出力画像のメモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++)
        {
            // 5. 変換
            if (src_img.at<unsigned char>(y, x) < 121)
            {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}

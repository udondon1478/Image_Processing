#include <iostream>
#include <opencv2/opencv.hpp>

#define COLOR_MAX (256)

#define FILE_NAME "/Users/x22004xx/src/imgProc/第4回/debug/red_rectangle.jpg"

int main(int argc, char const *argv[])
{
    // 1. 変数の宣言
    int i, x, y; // アクセス用の変数

    int hist[COLOR_MAX]; // ヒストグラム用の配列

    // 2. 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened %s\n", FILE_NAME);
        return (-1);
    }

    // 3. ヒストグラム用配列の初期化
    for (i = 0; i < COLOR_MAX; i++)
    {
        hist[i] = 0;
    }

    // 4. ヒストグラムの生成
    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++)
        {
            // 画素値の取得
            unsigned char s = src_img.at<unsigned char>(y, x);
            hist[(int)s]++; // 画素値の計算
        }
    }

    // 5. 出力(Numbers or Excel用に印字)
    for (i = 0; i < COLOR_MAX; i++)
    {
        printf("%d %d\n", i, hist[i]);
    }
    return 0;
}

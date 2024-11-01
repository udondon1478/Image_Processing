#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "/Users/x22004xx/src/imgProc/第三回/03_02/apple_tree.jpg"

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256) // 階調数
#define IMAX (255)      // 最大階調数

int main(int argc, char const *argv[])
{
    int n; // 階調数の分割数
    printf("階調数を入力してください\n");
    scanf("%d", &n);
    // 入力画像の読み込み(グレースケール入力)
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty()) // 読込み失敗時のエラー処理
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    // 出力画像のメモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
    uchar lut[COLOR_NUM]; // ルックアップテーブル変数の宣言
    // 指定された階調数のルックアップテーブル
    for (int i = 0; i < COLOR_NUM; i++)
    {
        lut[i] = (uchar)(i / (COLOR_NUM / n) * (IMAX / (n - 1)));
    }

    // ルックアップテーブルに基づいたポスタリゼーション
    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            dst_img.at<uchar>(y, x) = lut[src_img.at<uchar>(y, x)];
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);  // 入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示

    cv::waitKey(); // キー入力待ち(無限)
    return 0;
}

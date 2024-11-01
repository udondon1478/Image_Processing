#include <iostream>
#include <opencv2/opencv.hpp>

// 画像ファイル(小さめが良い)
#define FILE_NAME "/Users/x22004xx/src/imgProc/第2回/チャレンジ課題/aquarium.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[])
{
    int x, y;
    int n;

    scanf("%d", &n);

    // 画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME);
    if (src_img.empty())
    { // 入力失敗の場合
        return (-1);
    }

    // 出力画像のメモリ確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++) // 横方向
        {
            // 画素数の取得
            if (y >= src_img.rows / 2 - n / 2 && y <= src_img.rows / 2 + n / 2 && x >= src_img.cols / 2 - n / 2 && x <= src_img.cols / 2 + n / 2)
            {
                cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
                s[0] = 255; // B
                s[1] = 255; // G
                s[2] = 255; // R
                dst_img.at<cv::Vec3b>(y, x) = s;
            }
            else
            {

                cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
                s[0] = s[0]; // B
                s[1] = s[1]; // G
                s[2] = s[2]; // R
                dst_img.at<cv::Vec3b>(y, x) = s;
            }
        }
    }
    cv::imshow(WINDOW_NAME_INPUT, src_img);  // 画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 画像の表示
    cv::waitKey();                           // キー入力待ち(止める)
    return 0;
}

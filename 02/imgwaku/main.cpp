#include <iostream>
#include <opencv2/opencv.hpp>

// 画像ファイル(小さめが良い)
#define FILE_NAME "/Users/x22004xx/src/imgProc/第2回/pixelScan/aquarium.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[])
{
    int x, y;

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
        // 画素数の取得
        {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            s[0] = s[0]; // B
            s[1] = s[1]; // G
            s[2] = s[2]; // R
            if (x < 10 || src_img.cols - 10 <= x || y < 10 || src_img.rows - 10 <= y)
            {
                s[0] = 0;    // B
                s[1] = 0;    // G
                s[2] = 0;    // R }else{
                s[0] = s[0]; // B s[1] = s[1]; //G s[2] = s[2]; //R
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }
    cv::imshow(WINDOW_NAME_INPUT, src_img);  // 画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 画像の表示
    cv::waitKey();                           // キー入力待ち(止める)
    return 0;
}

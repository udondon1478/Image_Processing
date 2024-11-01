#include <iostream>
#include <opencv2/opencv.hpp>

// ファイル
#define FILE_NAME "../challenge.jpg"
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

// 二値化しきい値
#define BIN_TH (200)

int main(int argc, char **argv)
{
    // 1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    // 2. 輪郭の座標リストの宣言
    std::vector<std::vector<cv::Point>> contours;

    // 3. 画像の入力 (カラー)
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        std::cout << "Cannot open image file." << std::endl;
        return -1;
    }

    // 4. 入力画像を出力画像にコピー
    dst_img = src_img.clone();

    // 5. グレースケール化
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    // 6. 二値化 (固定しきい値で実装．しきい値: 200)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

    // 7. 二値画像コピー
    tmp_img = bin_img.clone();

    // 8. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    int count = 0;
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        if (area >= 50)
        {
            count++;
        }
    }

    std::cout << "50ピクセルを上回る白斑点の個数: " << count << std::endl;

    // 9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(0);

    return 0;
}

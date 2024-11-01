#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "/Users/x22004xx/src/imgProc/第三回/grayImg/apple_tree.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[])
{
    // 入力画像の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME);
    if (src_img.empty())    //読込み失敗時のエラー処理
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    //出力画像のメモリ確保
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
    //グレースケール変換
    //画像の走査
    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            //画素値を取得
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            uchar val = 0.114 * s[0]  //B
                      + 0.587 * s[1]  //G
                      + 0.299 * s[2]; //R
            //グレースケール変換
            gray_img.at<uchar>(y, x) = val;
        }
    }

    //出力画像の変数宣言 (グレースケール)
    cv::Mat dst_img;
    //グレースケール化(カラー => グレー)
    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);

    cv::imshow(WINDOW_NAME_INPUT, src_img);     //入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, gray_img);   //出力画像の表示

    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);   //出力画像の表示

    cv::waitKey();  //キー入力待ち(無限)
    return 0;
}


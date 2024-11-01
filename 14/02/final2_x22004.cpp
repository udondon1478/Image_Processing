#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../input2.jpg"
#define TH_BLACK (100)
#define TH_WHITE (150)

#define H_NUM (8)
#define W_NUM (8)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_GRAY "gray"
int main(int argc, char const *argv[])
{
    // 読み込まれたオセロ盤の画像から、黒と白の石が何個あるかを検出し、個数をテキストで出力するプログラム
    int black = 0, white = 0;

    // 1.画像の読み込み
    cv::Mat input_image = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    // 出力画像用の変数
    cv::Mat dst_image;
    // input_imageをdst_imageにクローン
    input_image.copyTo(dst_image);

    if (input_image.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    // 2.グレースケール化
    cv::Mat gray_image;
    cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);

    // 3.エッジ検出
    cv::Mat edge_image;
    cv::Canny(gray_image, edge_image, 50, 200, 3);

    // 4.エッジをつなげて石の領域を検出
    cv::Mat dilate_image;
    cv::dilate(edge_image, dilate_image, cv::Mat(), cv::Point(-1, -1), 2);

    // 5.石の領域の色を判定して、白い石と黒い石に分類する。
    // 5-1.白い石の領域を検出
    cv::Mat white_image;
    cv::threshold(gray_image, white_image, TH_WHITE, 255, cv::THRESH_BINARY_INV);

    // 5-2.黒い石の領域を検出
    cv::Mat black_image;
    cv::threshold(gray_image, black_image, TH_BLACK, 255, cv::THRESH_BINARY);

    // 6.石の領域を検出した画像から、石の個数を数える。
    // 6-1.white_imageの輪郭を検出
    std::vector<std::vector<cv::Point>> white_contours;
    cv::findContours(white_image, white_contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // 6-2.円形度が80%以上の輪郭の個数を数える
    for (int i = 0; i < white_contours.size(); i++)
    {
        // 輪郭の面積を計算
        double area = cv::contourArea(white_contours[i]);
        // 輪郭の周囲長を計算
        double arclen = cv::arcLength(white_contours[i], true);
        // 輪郭の面積と周囲長から円形度を計算
        double circularity = 4 * CV_PI * area / (arclen * arclen);
        // 円形度が80%以上の輪郭の個数を数える
        if (circularity > 0.8)
        {
            white++;
        }
    }

    // 6-3.black_imageを2回dilate
    cv::dilate(black_image, black_image, cv::Mat(), cv::Point(-1, -1), 2);
    cv::dilate(black_image, black_image, cv::Mat(), cv::Point(-1, -1), 2);

    // 6-4.black_imageの輪郭を検出
    std::vector<std::vector<cv::Point>> black_contours;
    cv::findContours(black_image, black_contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // 6-5.円形度が80%以上の輪郭の個数を数える

    for (int i = 0; i < black_contours.size(); i++)
    {
        // 輪郭の面積を計算
        double area = cv::contourArea(black_contours[i]);
        // 輪郭の周囲長を計算
        double arclen = cv::arcLength(black_contours[i], true);
        // 輪郭の面積と周囲長から円形度を計算
        double circularity = 4 * CV_PI * area / (arclen * arclen);
        // 円形度が80%以上の輪郭の個数を数える
        if (circularity > 0.8)
        {
            black++;
        }
    }

    // 7.石の個数をテキストで出力する。
    std::cout << "black:" << black << std::endl;
    std::cout << "white:" << white << std::endl;

    // 画像の表示
    cv::imshow(WINDOW_NAME_INPUT, input_image);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_image);
    cv::imshow(WINDOW_NAME_GRAY, gray_image);
    cv::imshow("edge", edge_image);
    cv::imshow("dilate", dilate_image);
    cv::imshow("white", white_image);
    cv::imshow("black", black_image);

    cv::waitKey(0);

    return 0;
}
// Github copilotを使用
// プロンプトは上記の番号がついている文章をそのまま使用

//7月29日 1:30 自動インデントを行ったか不明なため、自動インデントを行ったのち、再提出
//7月31日 14:16 x22001 青嶋瑠捺とx22052 島崎流奈に相談を受け、回答しました。
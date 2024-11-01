#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../gem2.jpg"
#define HUE_MIN (20)  // Hの最小値
#define HUE_MAX (60)  // Hの最大値
#define SAT_MIN (100) // Sの最小値
#define SAT_MAX (200)
#define R_MIN (0)   // Rの最小値
#define R_MAX (50)  // Rの最大値
#define G_MIN (50)  // Gの最小値
#define G_MAX (100) // Gの最大値// Sの最小値
#define TH (20)
#define MAX_VAL (255)
#define COUNT (15)
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    // 1-1.画像変数の宣言
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img, hsv_img, dst2_img, dst3_img;
    int x, y;
    cv::Vec3b p;

    // 1-2.輪郭の座標リストの宣言
    std::vector<std::vector<cv::Point>> contours;

    // 1-3. 画像を入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        std::cout << "File not found" << std::endl;
        return -1;
    }

    // 1-4. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

    // 1-5. 二値化
    cv::threshold(gray_img, bin_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);

    // 1-6. クロージング・オープニング
    cv::dilate(bin_img, tmp_img, cv::Mat(), cv::Point(-1, -1), COUNT);
    cv::erode(tmp_img, bin_img, cv::Mat(), cv::Point(-1, -1), COUNT * 2);
    cv::dilate(bin_img, tmp_img, cv::Mat(), cv::Point(-1, -1), COUNT);

    // 1-7. 輪郭追跡による領域検出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    dst_img = src_img.clone(); // 入力画像を出力画像にコピー

    for (int i = 0; i < contours.size(); i++)
    {
        cv::Rect bb;
        bb = cv::boundingRect(contours[i]);
        cv::rectangle(dst_img, bb, CV_RGB(255, 0, 0), 2);
    }

    // 1-8. 個数を出力
    std::cout << "Black gem = " << contours.size() << std::endl;

    contours.clear();

    // 1-9. 出力二値画像の領域を確保
    dst2_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 1-10. HSV変換
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    // 1-11. しきい値処理
    for (y = 0; y < hsv_img.rows; y++)
    {
        for (x = 0; x < hsv_img.cols; x++)
        {
            p = hsv_img.at<cv::Vec3b>(y, x);
            if (p[0] >= HUE_MIN && SAT_MIN <= p[1] && p[1] <= SAT_MAX && HUE_MAX >= p[0])
            {
                dst2_img.at<uchar>(y, x) = MAX_VAL;
            }
        }
    }

    // 2-1. クロージング・オープニング
    cv::dilate(dst2_img, dst2_img, cv::Mat(), cv::Point(-1, -1), COUNT);
    cv::erode(dst2_img, dst2_img, cv::Mat(), cv::Point(-1, -1), COUNT * 2);
    cv::dilate(dst2_img, dst2_img, cv::Mat(), cv::Point(-1, -1), COUNT);

    tmp_img = dst2_img;

    // 2-2. 輪郭追跡による領域検出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // 2-3. 外接円を描画
    // 入力画像を出力画像にコピー
    for (int i = 0; i < contours.size(); i++)
    {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contours[i], center, radius);
        cv::circle(dst_img, center, (int)radius, CV_RGB(255, 255, 255), 2);
    }

    // 2-4. 個数を出力
    std::cout << "golden gem = " << contours.size() << std::endl;

    contours.clear();

    dst3_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 2-4. しきい値処理
    for (y = 0; y < src_img.rows; y++)
    {
        for (x = 0; x < src_img.cols; x++)
        {
            p = src_img.at<cv::Vec3b>(y, x);
            if (p[2] >= R_MIN && G_MIN <= p[1] && p[1] <= G_MAX && R_MAX >= p[2])
            {
                dst3_img.at<uchar>(y, x) = MAX_VAL;
            }
        }
    }

    // 3-1. クロージング・オープニング
    cv::dilate(dst3_img, dst3_img, cv::Mat(), cv::Point(-1, -1), COUNT);
    cv::erode(dst3_img, dst3_img, cv::Mat(), cv::Point(-1, -1), COUNT * 2);
    cv::dilate(dst3_img, dst3_img, cv::Mat(), cv::Point(-1, -1), COUNT);

    tmp_img = dst3_img;

    // 3-2. 輪郭追跡による領域検出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++)
    {
        cv::drawContours(dst_img, contours, i, CV_RGB(0, 255, 0), cv::FILLED);
    }

    // 3-3. 個数を出力
    std::cout << "green gem = " << contours.size() << std::endl;

    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); // キー入力待ち (止める)

    return 0;
}

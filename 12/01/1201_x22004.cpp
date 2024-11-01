#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "../gazoDora.jpg"

#define TEMPLATE_IMG_GREEN "../green.jpg"
#define TEMPLATE_IMG_RED "../red.jpg"
#define TEMPLATE_IMG_STAR "../star.jpg"
#define TEMPLATE_IMG_YELLOW "../yellow.jpg"

#define WINDOW_INPUT "Input Image"
#define WINDOW_OUTPUT "Output Image"

int main(int argc, char const *argv[])
{
    // 与えられた画像からテンプレートを利用して各要素を検出せよ．
    // 検出はテンプレートと同じ色値で矩形で描画

    // 変数の宣言
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s;
    cv::Mat src_img, compare_img, result_img;

    // 画像の読み込み
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");

        return (-1);
    }

    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); // 画像のコピー

    // 緑、赤、ピンク、黄のRGBの色値をcolor配列に格納
    int color[4][3] = {{0, 255, 0}, {0, 0, 255}, {255, 0, 255}, {0, 255, 255}};

    // テンプレート画像を読み込み
    cv::Mat template_img_green = cv::imread(TEMPLATE_IMG_GREEN);
    cv::Mat template_img_red = cv::imread(TEMPLATE_IMG_RED);
    cv::Mat template_img_star = cv::imread(TEMPLATE_IMG_STAR);
    cv::Mat template_img_yellow = cv::imread(TEMPLATE_IMG_YELLOW);

    // テンプレート画像を配列に格納
    std::vector<cv::Mat> template_img_list;
    template_img_list.push_back(template_img_green);
    template_img_list.push_back(template_img_red);
    template_img_list.push_back(template_img_star);
    template_img_list.push_back(template_img_yellow);

    // テンプレートマッチング
    for (int i = 0; i < template_img_list.size(); i++)
    {
        // 類似度マップ
        compare_img = cv::Mat(cv::Size(src_img.cols - template_img_list[i].cols + 1, src_img.rows - template_img_list[i].rows + 1), CV_32F, 1);

        // テンプレートマッチング
        cv::matchTemplate(src_img, template_img_list[i], compare_img, cv::TM_SQDIFF_NORMED);

        // 最小値・最大値・その位置を取得
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

        // 閾値以下の位置を全て検出
        for (int y = 0; y < compare_img.rows; y++)
        {
            for (int x = 0; x < compare_img.cols; x++)
            {
                s = compare_img.at<float>(y, x);
                if (s <= 0.1)
                {
                    // 矩形を描画
                    cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img_list[i].cols, y + template_img_list[i].rows), cv::Scalar(color[i][0], color[i][1], color[i][2]), 4);
                }
            }
        }
    }

    // 画像の表示
    cv::imshow(WINDOW_INPUT, src_img);
    cv::imshow(WINDOW_OUTPUT, result_img);

    // キー入力待機
    cv::waitKey(0);

    return 0;
}
//
//  main.cpp
//  templateMatching4student
//
//  Created by sawano on 2015/07/05.
//  Modified by Tsukada  2021.07.06
//  Copyright (c) 2015年 AIT. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

// 全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../bg.jpg"

// テンプレート画像
#define TEMPLATE_IMG_FILE "../face.jpg"

//----------------------------

int main(int argc, const char *argv[])
{
    cv::Mat src_img, template_img, compare_img, result_img;
    double min_val=0.1, max_val=0.0;
    cv::Point min_loc, max_loc;
    float s; // 類似度マップはfloat型
    

    // 入力画像
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");

        return (-1);
    }

    // テンプレート画像
    template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);

    // 類似度マップ (1チャンネル)
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);

    // 結果画像
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); // 画像のコピー

    // ここまでが初期化 (前処理)
    //------------------------------------------------------------

    // テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");

    // ここに書く
    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

    fprintf(stderr, "テンプレートマッチングの終了\n");

    // 類似度マップの最小値最大値の計算
    for (int y=0; y<compare_img.rows; y++) {
        for (int x=0; x<compare_img.cols; x++) {
            s = compare_img.at<float>(y, x);    //float型で取得
            if (s < 0.05) {  //類似度が0.1以下の場合
                //長方形を描画
                cv::rectangle(result_img, cv::Point(x, y), cv::Point(x + template_img.cols, y + template_img.rows), CV_RGB(255, 0, 0), 3);
                fprintf(stderr, "x=%d, y=%d, s=%f\n", x, y, s);

            }
        }
    }

    // 長方形の表示

    // 　ここに書く
    cv::rectangle(result_img, min_loc, cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows), CV_RGB(255, 0, 0), 3);

    // 探索画像の描画
    cv::imshow("input", src_img);         // 入力画像
    cv::imshow("template", template_img); // テンプレート画像
    cv::imshow("result", result_img);     // 結果画像
    // キー入力待ち
    cv::waitKey(0);

    return 0;
}

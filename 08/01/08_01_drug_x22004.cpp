#include <iostream>
#include <opencv2/opencv.hpp>

#define IMG_NUM (8)
#define BUF (256)

int main()
{
    // 画像を読み込む
    for (int i = 0; i < IMG_NUM; i++)
    {
        cv::Mat src_img, dst_img;
        int white_pixels = 0;

        char file_name[BUF];
        snprintf(file_name, sizeof(file_name), "../drug%d.png", i);
        printf("file_name: %s\n", file_name);

        // ファイルの読み込み(グレースケール)
        src_img = cv::imread(file_name, 0);

        if (src_img.empty())
        {
            fprintf(stderr, "Failed to open file: %s\n", file_name);
        }

        // 画像サイズから総画素数の計算
        int width = src_img.cols;
        int height = src_img.rows;
        int total_pixels = width * height;

        // 二値化
        cv::threshold(src_img, dst_img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

        // 白画素の面積取得
        for (int y = 0; y < dst_img.rows; y++)
        {
            for (int x = 0; x < dst_img.cols; x++)
            {
                unsigned char s = dst_img.at<unsigned char>(y, x);
                if (s == 255)
                {
                    white_pixels++;
                }
            }
        }

        // 画像サイズに対して面積により判定
        if (white_pixels < (20 - 3) * total_pixels / 100)
        {
            fprintf(stderr, "欠損\n");
        }
        else if (white_pixels > (20 + 3) * total_pixels / 100)
        {
            fprintf(stderr, "膨張\n");
        }
        else
        {
            fprintf(stderr, "正常\n");
        }
        // 画像の表示
        cv::imshow("src_img", src_img);
        cv::waitKey(0);
    }
    return 0;
}

//x22041 近藤 秀祐と協力しました
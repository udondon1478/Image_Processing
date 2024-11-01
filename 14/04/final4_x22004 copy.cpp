#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../input2.jpg"
#define FILE_NAME2 "../input4.jpg"
#define TH_BLACK (100)
#define TH_WHITE (150)

#define H_NUM (8)
#define W_NUM (8)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_GRAY "gray"
int main(int argc, char const *argv[])
{
    // 読み込まれたオセロ盤の画像FILE_NAMEとオセロ盤の画像FILE_NAME2を比較し、追加された石の位置を検出するプログラム

    // 1.画像の読み込み
    cv::Mat input_image = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    cv::Mat input_image2 = cv::imread(FILE_NAME2, cv::IMREAD_COLOR);

    if (input_image.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    if (input_image2.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    // 2.グレースケール変換
    cv::Mat gray_image, gray_image2;
    cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);
    cv::cvtColor(input_image2, gray_image2, cv::COLOR_BGR2GRAY);

    // 4.FILE_NAMEとFILE_NAME2を比較し、色が変わった石は検出せず、追加された石のみ検出する
    cv::Mat dst_image;
    dst_image = input_image.clone();

    cv::Mat tmp_image;
    tmp_image = input_image.clone();
    for (int y = 0; y < input_image.rows; y++)
    {
        for (int x = 0; x < input_image.cols; x++)
        {
            // グレースケール画像から画素値を取得
            uchar pix1 = gray_image.at<uchar>(y, x);
            uchar pix2 = gray_image2.at<uchar>(y, x);

            // 画素値の差分が大きい場合、石が裏返されたと判断
            // 裏返された石が白だった場合、黒に塗りつぶす、黒だった場合、白に塗りつぶす
            if (abs(pix1 - pix2) > 50)
            {
                if (pix1 > pix2)
                {
                    tmp_image.at<cv::Vec3b>(y, x)[0] = 255;
                    tmp_image.at<cv::Vec3b>(y, x)[1] = 255;
                    tmp_image.at<cv::Vec3b>(y, x)[2] = 255;
                }
                else
                {
                    tmp_image.at<cv::Vec3b>(y, x)[0] = 0;
                    tmp_image.at<cv::Vec3b>(y, x)[1] = 0;
                    tmp_image.at<cv::Vec3b>(y, x)[2] = 0;
                }
            }
        }
    }

    // 5.input_imageとtmp_imageを比較し、追加された石の位置を検出する
    // 盤面を8*8に分割し、左上を原点(1,1)として、追加された石の位置を検出する

    // 5-1.配列を使って、盤面を8*8に分割する
    // 画像の高さ、幅を取得する
    int height = tmp_image.rows;
    int width = tmp_image.cols;

    // 画像の高さ、幅を8*8に分割する
    int h = height / H_NUM;
    int w = width / W_NUM;

    // 5-2.各領域の中心画素値を取得する
    // 各領域の中心画素値を格納する配列を宣言する
    int pix_input[H_NUM][W_NUM];
    int pix_tmp[H_NUM][W_NUM];

    // 各領域の中心画素値を取得する
    for (int i = 0; i < H_NUM; i++)
    {
        for (int j = 0; j < W_NUM; j++)
        {
            pix_input[i][j] = input_image.at<cv::Vec3b>(h * i + h / 2, w * j + w / 2)[0];
            pix_tmp[i][j] = tmp_image.at<cv::Vec3b>(h * i + h / 2, w * j + w / 2)[0];
        }
    }

    // 5-3.pix_inputとpix_tmpを比較し、格納されている値が違う場所を出力
    for (int i = 0; i < H_NUM; i++)
    {
        for (int j = 0; j < W_NUM; j++)
        {
            if (pix_input[i][j] != pix_tmp[i][j])
            {
                // 画素値がTH_WHITEより大きい場合、黒の石が追加されている
                if (pix_tmp[i][j] > TH_WHITE)
                {
                    std::cout << "black" << j + 1 << "-" << i + 1 << std::endl;
                }
                // 画素値がTH_BLACKより小さい場合、白の石が追加されている
                else if (pix_tmp[i][j] < TH_BLACK)
                {
                    std::cout << "white: " << j + 1 << "-" << i + 1 << std::endl;
                }
            }
        }
    }

    // 画像の表示
    cv::imshow(WINDOW_NAME_INPUT, input_image);
    cv::imshow("input2", input_image2);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_image);
    cv::imshow(WINDOW_NAME_GRAY, gray_image);
    cv::imshow("gray2", gray_image2);
    cv::imshow("tmp", tmp_image);

    cv::waitKey(0);

    return 0;
}
// Github copilotを使用
// プロンプトは上記の番号がついている文章をそのまま使用

// x22041 近藤秀祐にアルゴリズムを教えました

// 7月31日 14:16 x22001 青嶋瑠捺とx22052 島崎流奈に相談を受け、回答しました。
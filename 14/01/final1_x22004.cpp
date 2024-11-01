#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "../input1.jpg"
#define THRESHOLD (80)
#define THRESHOLD2 (70)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_BINARY "binary"
int main(int argc, char const *argv[])
{
    // 読み込まれたオセロ盤の画像から、盤面を仕切る黒線の枠を抽出し、赤線で描画するプログラム

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
    // 領域確保
    gray_image.create(input_image.rows, input_image.cols, CV_8UC1);
    cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);

    // 3.2値化
    cv::Mat bin_image;
    // 領域確保
    bin_image.create(input_image.rows, input_image.cols, CV_8UC1);
    cv::threshold(gray_image, bin_image, THRESHOLD, 255, cv::THRESH_BINARY);

    // 4.縦横それぞれから輝度値のヒストグラムをとる
    int x, y, i;

    // 4-1.画像の縦横のサイズを測る
    int width = input_image.cols;
    int height = input_image.rows;

    // 配列番号がx方向の座標、中に格納されるデータが輝度値のヒストグラムを作成
    int x_hist[width][height];
    // 配列番号がy方向の座標、中に格納されるデータが輝度値のヒストグラムを作成
    int y_hist[height][width];
    // 4-2.初期化
    for (i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            x_hist[i][j] = 0;
        }
    }

    for (i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            y_hist[i][j] = 0;
        }
    }

    // 4-3.ヒストグラムの作成

    // 4-3-1.x方向のヒストグラム(bin_imageの現在座標の画素値を配列に格納)
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            x_hist[x][y] = bin_image.at<unsigned char>(y, x);
        }
    }

    // 4-3-2.y方向のヒストグラム
    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            y_hist[y][x] = bin_image.at<unsigned char>(y, x);
        }
    }

    // 5-1.x方向のヒストグラムの画素値が0の時が連続してTHRESHOLD2以上の場合、該当x軸を赤く塗りつぶす
    for (y = 0; y < height; y++)
    {
        int count = 0;
        for (x = 0; x < width; x++)
        {
            if (x_hist[x][y] == 0)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count >= THRESHOLD2)
            {
                for (int i = 0; i < THRESHOLD2; i++)
                {
                    dst_image.at<cv::Vec3b>(y, x - i)[0] = 0;
                    dst_image.at<cv::Vec3b>(y, x - i)[1] = 0;
                    dst_image.at<cv::Vec3b>(y, x - i)[2] = 255;
                }
            }
        }
    }

    // 5-2.y方向のヒストグラムの画素値が0の時が連続してTHRESHOLD2以上の場合、該当y軸を赤く塗りつぶす
    for (x = 0; x < width; x++)
    {
        int count = 0;
        for (y = 0; y < height; y++)
        {
            if (y_hist[y][x] == 0)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count >= THRESHOLD2)
            {
                for (int i = 0; i < THRESHOLD2; i++)
                {
                    dst_image.at<cv::Vec3b>(y - i, x)[0] = 0;
                    dst_image.at<cv::Vec3b>(y - i, x)[1] = 0;
                    dst_image.at<cv::Vec3b>(y - i, x)[2] = 255;
                }
            }
        }
    }

    // 6.画像の表示
    cv::imshow(WINDOW_NAME_INPUT, input_image);
    cv::imshow(WINDOW_NAME_BINARY, bin_image);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_image);

    cv::waitKey(0);

    return 0;
}
// Github copilotを使用
// プロンプトは上記の番号がついている文章をそのまま使用

// x22041 近藤秀祐にアルゴリズムを教えました

//7月29日 1:28 自動インデントを行ったか不明なため、自動インデントを行ったのち、再提出
//7月31日 14:16 x22001 青嶋瑠捺とx22052 島崎流奈に相談を受け、回答しました。
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[])
{
  // 画像の読み込み
  cv::Mat img = cv::imread("drug4.jpg");

  // 画像サイズから総画素数の計算
  int width = img.cols;
  int height = img.rows;
  int total_pixels = width * height;

  // 二値化
  cv::threshold(img, img, 128, 255, cv::THRESH_BINARY);

  // 白画素の面積取得
  int white_pixels = cv::countNonZero(img);

  // 画像サイズに対して面積により判定
  if (white_pixels < (20 - 4) * total_pixels / 100)
  {
    std::cout << "欠損" << std::endl;
  }
  else if (white_pixels > (20 + 4) * total_pixels / 100)
  {
    std::cout << "膨張" << std::endl;
  }
  else
  {
    std::cout << "正常" << std::endl;
  }

  // 終了
  return 0;
  return 0;
}

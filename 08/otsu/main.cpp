#include <iostream>
#include <opencv2/opencv.hpp>

#define HIGHVAL (255) //白画素の値
#define TH (127) //閾値

#define FILE_NAME "../red_rectangle.jpg"

int main(int argc, const char * argv[]) {
    
    //画像をグレースケールで入力
    cv::Mat gray_img, bin_img;
    
    gray_img = cv::imread(FILE_NAME, 0);
    if (gray_img.empty()){ //入力失敗の場合
        fprintf(stderr,"File is not opened.\n");
        return (-1);
    }
    
    //二値化
    cv::threshold(gray_img, bin_img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    //表示
    cv::imshow("grayscale image", gray_img);//画像の表示
    cv::imshow("binary image", bin_img);//画像の表示
    cv::waitKey(); //キー入力待ち（止める）
    
    return 0;
}
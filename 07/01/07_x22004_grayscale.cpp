#include<iostream>
#include<opencv2/opencv.hpp>

#define FILE_NAME1 "../issue_input1.jpg"
#define FILE_NAME2 "../issue_input2.jpg"

#define THREDHOLD (8)

#define FILTER_SIZE (5)

#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, char const *argv[]){
    // 1. 画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    if(src_img2.empty() || src_img1.empty()){
        fprintf(stderr, "Failed to open file.\n");
        return -1;
    }

    // 2. ガウンシアンフィルタをinput2に適応
    cv::GaussianBlur(src_img2, src_img2, cv::Size(FILTER_SIZE, FILTER_SIZE), 0, 0);

    cv::Mat sub_img = cv::Mat(src_img1.size(), CV_8UC1);
    cv::Mat dst_img = cv::Mat(src_img1.size(), CV_8UC3);
    

    // 3. 画像の差分を取る
    int x, y;
    cv::Vec3b s;
    s[0] = 0;
    s[1] = 0;
    s[2] = 0;
    for(y = 0; y < src_img1.rows; y++){
        for(x = 0; x < src_img2.cols; x++){
            int s1 = (int)src_img1.at<uchar>(y, x);
            int s2 = (int)src_img2.at<uchar>(y, x);

            int s_result = abs(s1 - s2);
            sub_img.at<uchar>(y, x) = (uchar)s_result;


            // 4. 差分が閾値より大きければ赤、小さければ黒にする
            if(s_result > THREDHOLD)
                s[2] = 255;
            else
                s[2] = 0;
            
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }

    // 出力
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    return 0;
}
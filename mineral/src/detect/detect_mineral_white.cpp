
#include <mineral.h>
#include <rmserial.h>
#include <rmconfig.h>

/*
 * 函数说明
 * 1、用途：检测已经落在大资源岛上的矿石
 * 2、参数：
 *      Mat &operand摄像机读取的图像
 * 3、版本：Version 4.0
 */


void Mineral::detectWhiteMineral(Mat &operand) {
    //初始化
    all_fit_points.clear();
    all_fit_rects.clear();

    //形态学操作+gamma变换二值化
    Mat dst(operand.size(), CV_8UC1);
    MorWhiteMineral(operand,dst);

#ifdef DEBUG
    Mat BackGround = Mat::zeros(operand.size(), CV_8UC3);
    imshow("after Mor",dst);
    waitKey(1);
#endif

    //找轮廓
    vector<vector<Point>> Contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, 80, 100);
    findContours(dst, Contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    for (int i = 0; i < Contours.size(); i++) {
        if(arcLength(Contours[i],1) < g_para.mineral_white_threshold_length) continue;
        RotatedRect fit_rotated = minAreaRect(Contours[i]);
        Rect fit = boundingRect(Contours[i]);                                                       //矩形拟合合适的轮廓
        double area_rect = float(fit.width) * float(fit.height);
        double area_contour = contourArea(Contours[i]);
        double decrease = area_rect-area_contour;
        bool area_fit = float(fit_rotated.size.width) * float(fit_rotated.size.height) > g_para.mineral_white_threshold_area_low &&
                        float(fit_rotated.size.width) * float(fit_rotated.size.height) < g_para.mineral_white_threshold_area_high;             //通过区域面积筛选
        bool scale_fit = float(fit_rotated.size.width) / fit_rotated.size.height < g_para.mineral_white_threshold_scale_high &&                //通过长宽比筛选
                         float(fit_rotated.size.width) / fit_rotated.size.height > g_para.mineral_white_threshold_scale_low;
        if (scale_fit&&area_fit&&decrease>500) {
            all_fit_rects.push_back(fit);
#ifdef DEBUG
            rectangle(BackGround,fit, Scalar(255, 0, 0), 2);
            drawContours(BackGround, Contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }


    //计算中点
    getFitPoints(all_fit_rects,all_fit_points);


    //点集排序
    sortPointsVector(all_fit_points,X_INCREASE);
    Number_white = all_fit_points.size();


    //发送数据
    sendTarget();

    //调试
    for(auto item:all_fit_points){
        circle(BackGround,item,1,Scalar(0,255,0),4);
    }
    imshow("result_white",BackGround);
    waitKey(1);
    imshow("currrent",operand);
    waitKey(1);
}

//
// Created by ayb on 2021/7/10.
//
#include <mineral.h>

void Mineral::getFitContours(Mat &dst,Mat &BackGround) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Canny(dst, dst, g_para.mineral_threshold_canny_low, g_para.mineral_threshold_canny_high);//30,100
    findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //筛选轮廓
    for (int i = 0; i < contours.size(); i++) {
        Rect fit = boundingRect(contours[i]);                                                     //矩形拟合合适的轮廓
        bool scale_fit =
                float(fit.width) / fit.height < g_para.mineral_threshold_scale_high &&                //通过长宽比筛选
                float(fit.width) / fit.height > g_para.mineral_threshold_scale_low;
        bool area_fit = float(fit.width) * float(fit.height) > g_para.mineral_threshold_area_low &&
                        float(fit.width) * float(fit.height) <
                        g_para.mineral_threshold_area_high;             //通过区域面积筛选
        if (scale_fit && area_fit && hierarchy[i][3] != -1) {
            all_fit_rects.push_back(fit);
#ifdef DEBUG
            rectangle(BackGround, fit, Scalar(255, 0, 0), 2);
            drawContours(BackGround, contours, i, Scalar(0, 255, 0), 2);
#endif
        }
    }
}

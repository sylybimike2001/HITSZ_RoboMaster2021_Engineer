#include <mineral.h>

void Mineral::getFitPoints(std::vector<Rect> &fitRects,std::vector<Point> &fitPoints){
    for(int k=0;k<all_fit_rects.size();k++){
        Point center;
        center.x = all_fit_rects[k].x+all_fit_rects[k].width/2;
        center.y = all_fit_rects[k].y+all_fit_rects[k].height/2;
        fitPoints.push_back(center);
    }
    sortPointsVector(all_fit_points,Y_INCREASE);            //先升序排序
    if(!all_fit_points.empty()) {
        int size = all_fit_points.size();
        if (abs(all_fit_points[0].y - all_fit_points[size - 1].y) > 50) all_fit_points.pop_back();
        //如果有一个Y值和其他点相差较大很大的异常点，剔除它
    }
}
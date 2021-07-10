#include <mineral.h>

void Mineral::getTargetPoints(const std::vector<cv::Point> &all_fit_points, std::vector<Point> &target_points) {
    Point temp;
    for(int index =1;index<all_fit_points.size();index++){
        temp.x = (all_fit_points[index].x+all_fit_points[index-1].x)/2;
        temp.y = (all_fit_points[index].y+all_fit_points[index-1].y)/2;
        target_points.push_back(temp);
    }
}

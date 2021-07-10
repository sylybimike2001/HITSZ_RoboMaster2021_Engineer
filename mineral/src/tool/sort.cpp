#include <mineral.h>


void Mineral::sortPointsVector(vector<cv::Point> &all_fit_points,int flag){
    switch (flag) {
        case X_INCREASE:
        {
        sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
            return a.x < b.x;
            });
        }
            break;
        case X_DECREASE:
        {
        sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
            return a.x > b.x;
            });
        }
            break;
        case Y_INCREASE:
        {
            sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
                return a.y < b.y;
            });
        }
            break;
        case Y_DECREASE:
        {
            sort(all_fit_points.begin(), all_fit_points.end(), [](cv::Point &a, cv::Point &b) {
                return a.y > b.y;
            });
        }
            break;
    }

    vector<cv::Point>::iterator new_end;
    new_end = unique(all_fit_points.begin(),all_fit_points.end());
    all_fit_points.erase(new_end,all_fit_points.end());
}
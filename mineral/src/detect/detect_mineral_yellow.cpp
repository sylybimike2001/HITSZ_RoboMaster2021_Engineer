#include <mineral.h>


void Mineral::detectYellowMineral(const Mat &operand){
    if(initMineral()) {
        //形态学操作+HSV颜色分离
        Mat dst(operand.size(), CV_8UC3);
        MorYellowMineral(operand, dst);

#ifdef DEBUG
        Mat BackGround = Mat::zeros(operand.size(), CV_8UC3);
        imshow("after Mor", dst);
        waitKey(1);
#endif
        //找轮廓
        getFitContours(dst,BackGround);

        //对各矩形取中心点
        getFitPoints(all_fit_rects, all_fit_points);

        //对点集进行排序
        sortPointsVector(all_fit_points, X_INCREASE);

        //get target points:the center of each points
        getTargetPoints(all_fit_points, target_points);

        Number_yellow = target_points.size();

        //发送数据
        sendTarget();

        //调试
        for (auto item : all_fit_points) circle(BackGround, item, 2, Scalar(0, 255, 0), 2);
        for (auto item: target_points) circle(BackGround, item, 2, Scalar(0, 0, 255), 3);
        cout << "Number Yellow:" << Number_yellow << endl;
        imshow("result_yellow", BackGround);
        waitKey(1);
    }
}

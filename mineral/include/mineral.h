#include <rmconfig.h>
#include <parameter.h>
#include <data_manager.h>
using namespace std;
using namespace cv;
/*
 *代码说明
 * 1、摄像头参数：定焦150度广角镜头，定曝光1000
 * 2、检测说明：用来观测高处的矿石
 */

extern RmParameter g_para;

enum TemplateMatchModes {
    X_INCREASE  = 1,
    X_DECREASE = -1,
    Y_INCREASE  = 2,
    Y_DECREASE = -2
};

class Mineral{
public:
    /*
     * 函数说明：
     * 1、函数功能：初始化对象
     * 2、初始化列表：避免获取错误的初始值 来自Effective C++的经验
     */
    Mineral();


    /*
     * 函数说明：什么也没做，打算把一些初始化封装在此函数中
     */
    bool initMineral();                                                             //do nothing


    /*
     * 函数说明：未曾优化/实际测试
     * 1、用途：检测小资源岛上的矿石
     * 2、参数：
     *      Mat &operand摄像机读取的图像
     * 3、版本：Version 1.0
     */
    void detectWhiteMineral(Mat &operand);

    /*
     * 函数说明
     * 1、用途：检测已经落在大资源岛上的矿石
     * 2、参数：
     *      Mat &operand摄像机读取的图像
     * 3、版本：Version 4.0
     */
    void detectYellowMineral(const Mat &operand);

    /*
     * 函数说明：
     * 1、功能说明：通过串口给主控板通讯发送数据
     * 2、参数说明：无
     * 3、状态说明：      障碍块BARRICADE_AUTO_RUN 1
                        大资源岛 BIG_RESOURCE_ISLAND_AUTO_RUN 2
                        小资源岛 SMALL_RESOURCE_ISLAND_AUTO_RUN 3
                        悬空 FREE_MODE 4
     */
    bool sendTarget() ;

    /*
     * 函数说明：
     * 1、功能说明：获取所有合适矩形中心点
     * 2、参数说明：
     *          std::vector<Rect> &fitRects     筛选出的矩形轮廓
     *          std::vector<Point> &fitPoints   目标容器，将矩形中心点放入其中
     * 3、版本：Version 3.0
     */
    void getFitPoints(std::vector<Rect> &fitRects,std::vector<Point> &fitPoints);

    /*
     * 函数说明：
     * 1、功能说明：对传入的容器进行排序,剔除重复元素
     * 2、参数说明：vector<cv::Point> &all_fit_points 需要进行排序并剔除重复元素的容器
     *            int flag :    X_INCREASE  按X升序排列
                                X_DECREASE  按X降序排列
                                Y_INCREASE  按Y升序排列
                                Y_DECREASE  按Y降序排列
     * 3、版本：V3.0 （效率最大化）
     */
    void sortPointsVector(std::vector<cv::Point> &all_fit_points,int flag);

    /*
     * 函数说明：
     * 1、功能说明:gamma变换
     * 2、参数说明：Mat &image 原图像
     *            Mat &dist 输出图像
     * 3、版本 V1.0
     */
    void GammaTransform(Mat &image,Mat &dist);


    /*
     * 函数说明：
     * 1、功能说明:大资源岛主函数
     * 2、参数说明：V4L2Capture &cap 摄像头实例
     * 3、版本 V1.0
     */
    void runBigResourceIsland(V4L2Capture &cap);

    /*
     * 函数说明：
     * 1、功能说明:小资源岛主函数
     * 2、参数说明：V4L2Capture &cap 摄像头实例
     * 3、版本 V1.0
     */
    void runSmallResourceIsland(V4L2Capture & cap);

    /*
     * 函数说明：
     * 1、功能说明:获取对位目标点
     * 2、参数说明：
     *              const std::vector<cv::Point> &all_fit_points    所有合适矩形中心点容器
     *              std::vector<Point> &target_points               目标点容器
     * 3、版本 V1.0
     */
    void getTargetPoints(const std::vector<cv::Point> &all_fit_points,std::vector<Point> &target_points);

    void getSendData(SendData &data,int index);                                     //never used
    void getSendData(SendData &data);                                               //never used
    void MorMineral(Mat & operand,Mat &output);                                     //never used

    void MorYellowMineral(const Mat & operand,Mat &output) const;                   //Mor Yellow
    void MorWhiteMineral(Mat & operand,Mat &output);                                //Mor White

    void getFitContours(Mat &dst,Mat &BackGround);

private:
    std::vector<Rect>    all_fit_rects;
    std::vector<Point>   all_fit_points;
    std::vector<Point>   target_points;
    Mat src;
    bool locate_complete;
    int Number_yellow;
    int Number_white;
    static const int threshold_error = 324;

};

inline auto minPoint(Point first,Point second){
    if (abs(first.x-360)>(second.x-360))
        return second;
    else return first;
}

//inline auto minPoint(Point first,Point second,Point third){
//    Point temp;
//    temp = abs(first.x-360)>abs(second.x-360)?second:first;
//    temp = abs(first.x-360)>abs(third.x-360)?third:first;
//    temp = abs(second.x-360)>abs(third.x-360)?third:second;
//    return temp;
//}
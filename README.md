# HITSZ_RoboMaster2021_Engineer
# README

## 1、工程结构

~~~
── cmake-build-debug
├── CMakeLists.txt
├── com
│   ├── include
│   │   ├── data_manager.h
│   │   ├── datatypes.h
│   │   ├── rmserial.h
│   │   └── serial
│   │       ├── impl
│   │       │   ├── unix.h
│   │       │   └── win.h
│   │       ├── serial.h
│   │       └── v8sydint.h
│   └── src
│       ├── data_manager.cpp
│       ├── datatypes.cpp
│       ├── impl
│       │   ├── list_ports
│       │   │   └── list_ports_linux.cpp
│       │   └── unix.cpp
│       ├── rmserial.cpp
│       └── serial.cpp
├── main.cpp
├── Makefile
├── mineral
│   ├── include
│   │   └── mineral.h
│   ├── run.cpp
│   └── src
│       ├── detect
│       │   ├── detect_mineral_white.cpp
│       │   └── detect_mineral_yellow.cpp
│       ├── get
│       │   ├── get_fit_contours.cpp
│       │   ├── get_fit_points.cpp
│       │   ├── get_send_data.cpp
│       │   └── get_target_points.cpp
│       ├── init
│       │   ├── default_constructor.cpp
│       │   └── init_mineral.cpp
│       ├── locate
│       ├── mor
│       │   ├── mor_dropped_yellow_mineral.cpp
│       │   ├── mor_hang_high_mineral.cpp
│       │   └── mor_white_mineral.cpp
│       ├── send
│       │   └── send_target.cpp
│       └── tool
│           ├── gamma_transform.cpp
│           └── sort.cpp
├── rmconfig
│   ├── parameter.h
│   ├── rmconfig.h
│   ├── uvc_v4l2.cpp
│   └── uvc_v4l2.h
└── RoboMaster2021_Engineer_Final

~~~

## 2、功能说明

### （1）大资源岛对位

思路：

HSV颜色分离->形态学操作->轮廓提取->根据TREE父子轮廓筛选->矩形框选->比例筛选、面积筛选->得到特征矩形->根据Y方向差距排除差值最大的干扰点->计算中心点->发送数据

### (2)小资源岛对位

已开发，未测试

## 3、类说明

### （1）Mineral类

生存空间：

从程序开始执行直到程序结束

私有成员：

```c++
std::vector<cv::Rect>    all_fit_rects_;
								//筛选后的矩形
std::vector<cv::Point>   all_fit_points_;
								//排除所有异常点后的可用点
std::vector<cv::Point>   target_points_;
								//解算发送数据的目标点
cv::Mat src_;							//处理对象
bool locate_complete_;					//对位成功标志位
int Number_yellow_;						//黄色矿石数目
int Number_white_;						//白色矿石数目
static const int threshold_error = 324;	//图像阈值
```

成员函数：

```c++
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
void detectWhiteMineral(cv::Mat &operand);

/*
 * 函数说明
 * 1、用途：检测已经落在大资源岛上的矿石
 * 2、参数：
 *      Mat &operand摄像机读取的图像
 * 3、版本：Version 4.0
 */
void detectYellowMineral(const cv::Mat &operand);

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
void getFitPoints(std::vector<cv::Rect> &fitRects,std::vector<cv::Point> &fitPoints);

/*
 * 函数说明：
 * 1、功能说明：对传入的容器进行排序,剔除重复元素
 * 2、参数说明：vector<cv::Point> &all_fit_points_ 需要进行排序并剔除重复元素的容器
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
void GammaTransform(cv::Mat &image,cv::Mat &dist);


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
 *              const std::vector<cv::Point> &all_fit_points_    所有合适矩形中心点容器
 *              std::vector<Point> &target_points_               目标点容器
 * 3、版本 V1.0
 */
void getTargetPoints(const std::vector<cv::Point> &all_fit_points,std::vector<cv::Point> &target_points);

void getSendData(SendData &data,int index);                                     //never used
void getSendData(SendData &data);                                               //never used
void MorMineral(cv::Mat & operand,cv::Mat &output);                                     //never used

void MorYellowMineral(const cv::Mat & operand,cv::Mat &output) const;                   //Mor Yellow
void MorWhiteMineral(cv::Mat & operand,cv::Mat &output);                                //Mor White

void getFitContours(cv::Mat &dst,cv::Mat &BackGround);
```

### （2）DataManager类

生存时间：

使用智能指针管理，每次需要发送数据时创建，并对数据处理，发送数据后销毁

私有成员：

```c++
std::shared_ptr<SendData> data_;
//使用impl方法，将数据封装在外部结构体，类仅持有指针
```

成员函数：

```c++
DataManager(SendData *);

DataManager(shared_ptr<SendData>);

inline void update_error(const int & );

inline void update_direction(const char &);

int get_error(const int &Number_yellow,const 
              vector<cv::Point> &target_points);
bool update_state(const int &Number_yellow,const 
                  vector<cv::Point> &target_points);

void show_data() const;

~DataManager();
```


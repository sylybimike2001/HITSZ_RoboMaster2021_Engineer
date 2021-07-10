//
// Created by ayb on 2021/7/10.
//

#ifndef ROBOMASTER2021_ENGINEER_FINAL_DATA_MANAGER_H
#define ROBOMASTER2021_ENGINEER_FINAL_DATA_MANAGER_H

#include <memory>
#include <datatypes.h>
#include <rmconfig.h>
/*
 *  uint8_t start_flag;                         //帧头是‘s’
    uint16_t error_x;                           //矿石中间点和图像中心点（车正中心）的偏差
    uint8_t direction_x;                        //‘l’表示在图像视野左侧，‘r’表示图像在视野右侧
    uint8_t is_error_data;                      //标志本次是否为错误数据
    uint8_t is_standard;                        //图像x方向是否对齐（线是否水平)
    uint8_t end_flag;                           //帧尾是‘e’
 */
class DataManager{
public:
    DataManager(SendData *);
    DataManager(shared_ptr<SendData>);
    inline void update_error(const int & );
    inline void update_direction(const char &);
    int get_error(const int &Number_yellow,const vector<cv::Point> &target_points);
    bool update_state(const int &Number_yellow,const vector<cv::Point> &target_points);
    void show_data() const;
    ~DataManager();
private:
    std::shared_ptr<SendData> data_;

};
#endif //ROBOMASTER2021_ENGINEER_FINAL_DATA_MANAGER_H

//
// Created by ayb on 2021/7/10.
//

#ifndef ROBOMASTER2021_ENGINEER_FINAL_DATA_MANAGER_H
#define ROBOMASTER2021_ENGINEER_FINAL_DATA_MANAGER_H

#include <memory>
#include <datatypes.h>
#include <rmconfig.h>

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

//
// Created by ayb on 2021/7/10.
//
#include <data_manager.h>
#include <mineral.h>

DataManager::DataManager(SendData *new_data):data_(new_data) {    //不如就使用pimpl手法!,注意shared_ptr构造函数只接受非const
    data_->start_flag    = 's';
    data_->is_error_data = 0;
    data_->is_standard   = 0;
    data_->error_x       = 0;
    data_->end_flag      = 'e';
}

DataManager::DataManager(shared_ptr<SendData> new_data):data_(new_data) {
    data_->start_flag    = 's';
    data_->is_error_data = 0;
    data_->is_standard   = 0;
    data_->error_x       = 0;
    data_->end_flag      = 'e';
}

void DataManager::update_error(const int &new_error){
    data_->error_x = new_error;
}

void DataManager::update_direction(const char &new_dir) {
    data_->direction_x = static_cast<int>(new_dir);             //ASC?
}

int DataManager::get_error(const int &Number_yellow,const vector<cv::Point> &target_points) {
    int error_x=0;
    if(Number_yellow == 1) error_x = target_points[0].x-g_para.src_width_/2+g_para.offset;
    else if(Number_yellow == 2) error_x = minPoint(target_points[0],target_points[1]).x-g_para.src_width_/2+g_para.offset;
    else if(Number_yellow == 0){
        data_->is_error_data = 1;
        cout<<"Wrong:"<<data_->error_x<<endl;
        error_x = g_para.error_max;
    }
    return error_x;
}

bool DataManager::update_state(const int &Number_yellow,const vector<cv::Point> &target_points) {
    int error = get_error(Number_yellow,target_points);
    if (error < 0) {
        update_direction('l');
        update_error(0-error);
        if (data_->error_x > g_para.error_max) update_error(g_para.error_max);
    } else {
        update_direction('r');
        update_error(error);
        if (data_->error_x > g_para.error_max) update_error(g_para.error_max);
    }
    if (data_->error_x < g_para.mineral_threshold_error) {
        data_->is_standard = 1;
        cout<<"complete"<<endl;
        return true;
    }
    return false;
}

void DataManager::show_data() const {
    cout<<"Error X:"<<data_->error_x<<endl;
}

DataManager::~DataManager(){
}
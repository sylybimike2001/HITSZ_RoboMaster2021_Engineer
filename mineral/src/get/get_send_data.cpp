#include <mineral.h>
#include <datatypes.h>

/*
 * 函数说明：新框架不使用
 * １、功能：获得发送数据的结构体，适用于黄色矿石,大资源岛
 * ２、参数：　SendData &data　发送数据
 *          　int index      第几个矿石，默认为1
*/
void Mineral::getSendData(SendData &data,int index=1) {

    int error_x=0;
    if(Number_yellow == 1) error_x = target_points[0].x-src.size().width/2;
    else if(Number_yellow == 2) error_x = minPoint(target_points[0],target_points[1]).x-src.size().width/2;
    else if(Number_yellow == 0){
        data.is_error_data = 1;
        data.error_x = 255;
        cout<<"Wrong "<<data.error_x<<endl;
        return;
    }

    if (error_x < 0) {
        data.direction_x = 'l';
        data.error_x = 0 - error_x;
        if (data.error_x > threshold_error) data.error_x = threshold_error;
    } else {
        data.direction_x = 'r';
        data.error_x = error_x;
        if (data.error_x > threshold_error) data.error_x = threshold_error;
    }

    cout<<"Error X:"<<data.error_x<<endl;
    if (data.error_x < g_para.mineral_threshold_error) {
        data.is_standard = 1;
        locate_complete = 1;
        cout<<"complete"<<endl;
    }
}

/*
 * 函数说明：新框架不使用
 * １、功能：获得发送数据的结构体，适用于白色矿石
 * ２、参数：　SendData &data　发送数据所用结构体
 *
*/
void Mineral::getSendData(SendData &data){
    int error_x;
    if(Number_white==1){            //只有一个特征点，说明矿石在视野右侧（左侧），返回特征点中点
        data.is_error_data = 1;
        error_x = all_fit_points[0].x-(float)src.size().width/2;
    }
    else if(Number_white==3){       //有三个特征点，说明检测到了右侧相邻矿石的另一个特征点，或者干扰项，返回中间的一个特征点中点
        error_x = all_fit_points[1].x-(float) src.size().width / 2;
    }
    else if(Number_white==2){       //有两个特征点，正常情况
        int threshold = src.size().width / 3;
        error_x = (all_fit_points[0].x+all_fit_points[1].x)/2-(float)src.size().width/2;
        if (error_x < 0) {
            data.direction_x = 'l';
            data.error_x = 0 - error_x;
            if (data.error_x > threshold) data.error_x = threshold;     //输出限幅
        } else {
            data.direction_x = 'r';
            data.error_x = error_x;
            if (data.error_x > threshold) data.error_x = threshold;     //输出限幅
        }

        //使用默认值
        data.start_flag = 's';
        data.is_standard = 0;
        data.is_error_data = 0;
        data.end_flag = 'e';
        //水平方向误差小于阈值，退出自动对位

        if (data.error_x < g_para.mineral_threshold_error) {
            data.is_standard = 1;
            locate_complete = 1;
        }

#ifdef DEBUG
        cout<<"Data sent: "<<data.error_x<<endl;
#endif
    }
    else{
        data.is_error_data = 1;
        cout<<"Wrong Data"<<endl;
        return;
    }
}
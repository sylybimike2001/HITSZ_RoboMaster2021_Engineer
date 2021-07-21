#include <mineral.h>
#include <rmconfig.h>
using namespace std;
using namespace cv;
char devices[40] = "/dev/video0";

McuConfig g_config_data;                        //extern
RmSerial g_rmSerial;                            //extern
RmParameter g_para;                             //extern

inline void test_Free_Mode();
inline void test_Big_Island();
inline void test_Small_Island();
inline void show_current_frame(V4L2Capture cap_t);

int main()
{
    bool keepRunning =1;
    g_rmSerial.init();
    shared_ptr<Mineral> MineralDetector(new Mineral);
    V4L2Capture cap_t(devices, 720, 480);
    cap_t.set_exposure(300);
    test_Free_Mode();

    while(keepRunning){
        switch (g_config_data.state){
            case BIG_RESOURCE_ISLAND_AUTO_RUN:
            {
                cout << "Mode:BIG_RESOURCE_ISLAND_AUTO_RUN" << endl;
                MineralDetector->runBigResourceIsland(cap_t);      //进入函数内部等待单片机发出启动指令
            }
                break;
            case SMALL_RESOURCE_ISLAND_AUTO_RUN:{
                cout<< "Mode:SMALL_RESOURCE_ISLAND_AUTO_RUN"<<endl;
                cap_t.set_exposure(400);
                MineralDetector->runSmallResourceIsland(cap_t);
            }
                break;
            case FREE_MODE:
            {
                cout<< "Mode:FREE MODE"<<endl;
                Mat temp;
                cap_t>>temp;
                imshow("current frame",temp);
                waitKey(1);
            }
                break;
            default:
                return 0;
        }
    }
}


inline void test_Free_Mode(){
    g_config_data.start =0;
    g_config_data.state =FREE_MODE;
}
inline void test_Big_Island(){
    g_config_data.start =1;
    g_config_data.state =BIG_RESOURCE_ISLAND_AUTO_RUN;
}
inline void test_Small_Island(){
    g_config_data.start =1;
    g_config_data.state =SMALL_RESOURCE_ISLAND_AUTO_RUN;
}

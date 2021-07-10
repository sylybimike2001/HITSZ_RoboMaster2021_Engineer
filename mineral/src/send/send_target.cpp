#include <mineral.h>
#include <datatypes.h>
#include <rmconfig.h>

bool Mineral::sendTarget() {
    shared_ptr<SendData> data(new SendData);
    DataManager data_manager(data);
    if(g_config_data.state == BIG_RESOURCE_ISLAND_AUTO_RUN) {
        locate_complete = data_manager.update_state(Number_yellow,target_points);
        g_rmSerial.send_data(*data);
    }
    if(g_config_data.state == SMALL_RESOURCE_ISLAND_AUTO_RUN){
        locate_complete = data_manager.update_state(Number_white,target_points);
        g_rmSerial.send_data(*data);
    }
}
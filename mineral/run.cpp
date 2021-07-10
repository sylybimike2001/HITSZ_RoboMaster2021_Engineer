#include <mineral.h>

void Mineral::runBigResourceIsland(V4L2Capture &cap) {
    locate_complete = false;
    while (g_config_data.state == BIG_RESOURCE_ISLAND_AUTO_RUN &&
           g_config_data.start && !locate_complete)
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                cout << "frame empty" << endl;
                break;
            }
        }
        detectYellowMineral(src);
    }
}
void Mineral::runSmallResourceIsland(V4L2Capture & cap) {
    locate_complete = false;
    while (g_config_data.state == SMALL_RESOURCE_ISLAND_AUTO_RUN &&
           g_config_data.start && !locate_complete)
    {
        if (use_cam) {
            cap>>src;
            if (src.empty()) {
                cout<<"empty"<<endl;
                break;
            }
        }
        detectWhiteMineral(src);
    }
}
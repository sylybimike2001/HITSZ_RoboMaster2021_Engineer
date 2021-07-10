#include <datatypes.h>

void readEngineerMcuData(McuData* mcudata, uint8_t * start,uint8_t * state){
    *start = mcudata->start;
    *state = mcudata->type;
}
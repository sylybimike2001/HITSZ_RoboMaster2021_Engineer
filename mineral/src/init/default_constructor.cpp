#include <mineral.h>

Mineral::Mineral() :locate_complete(false),
                    Number_white(0),
                    Number_yellow(0),
                    src(Mat::ones(720,480,CV_8UC3)){
}
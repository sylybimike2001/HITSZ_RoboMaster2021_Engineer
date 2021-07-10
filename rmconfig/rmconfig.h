#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <rmserial.h>
#include <uvc_v4l2.h>

#define capture_index 0
#define use_cam 1
#define use_VideoCapture 1

#define DEBUG
#define __DEBUG__WRITER

#define BARRICADE_AUTO_RUN 1
#define BIG_RESOURCE_ISLAND_AUTO_RUN 2
#define SMALL_RESOURCE_ISLAND_AUTO_RUN 3
#define FREE_MODE 4
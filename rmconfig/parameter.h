struct RmParameter{
    /*
 * 参数说明：用于检测黄色矿石
 * 1、检测黄色矿石所使用的比例约束和面积约束
 * 2、比例约束：近距离基本不会出现干扰，比例容忍度较高
 * 3、面积约束：工程贴近资源岛时，黑色标志点面积很大，面积上限较高
 */
//detect mineral
    const double mineral_threshold_scale_low=0.8;
    const double mineral_threshold_scale_high=1.2;
    const double mineral_threshold_area_low=600;//70
    const double mineral_threshold_area_high=10000;//600
    const double mineral_threshold_canny_low=30;
    const double mineral_threshold_canny_high=100;


/*
 * 参数说明：
 * 1、用于检测高处矿石，粗对位，不建议使用
 * 2、仰角看矿石会扁，长宽比例阈值放大
 */
//detect mineral high
    const double mineral_high_threshold_scale_low=0.9;
    const double mineral_high_threshold_scale_high=1.8;
    const double mineral_high_threshold_area_low=400;
    const double mineral_high_threshold_area_high=160000;
    const double mineral_threshold_error=10;  //水平方向error小于10认为对位完成


/*
 * 参数说明：
 * 1、用于检测障碍块
 */

    const double barrier_threshold_scale_low =0.8;
    const double barrier_threshold_scale_high =1.2;
    const double barrier_threshold_area_low =100;
    const double barrier_threshold_area_high =160000;
    const double barrier_threshold_length =80;
    const double barrier_threshold_bin =30;

/*
 * 参数说明：
 * 1、用于检测小资源岛上白色矿石
 * 2、比例条件和面积条件比较苛刻
 * 3、二值化阈值说明：待补充
 */
    const double mineral_white_threshold_scale_low =0.9;
    const double mineral_white_threshold_scale_high =1.1;
    const double mineral_white_threshold_area_low =1600;
    const double mineral_white_threshold_area_high =10000;
    const double mineral_white_threshold_length =150;
    const double mineral_white_threshold_bin =30;


    const int src_width_ = 720;
    const int src_height_ = 480;
    const int error_max = 324;
    const int offset = 46;
};
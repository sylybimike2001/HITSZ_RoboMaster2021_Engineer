#include "../serial/v8sydint.h"
#include <thread>
#include <iostream>
#include <rmserial.h>
using namespace serial;

std::mutex receive_mtx;
const std::string uart_port = "/dev/ttyUSB0";


RmSerial::~RmSerial() { stop_thread(); }

bool RmSerial::send_data(uint8_t* data, size_t size) {
    return active_port->write(data, size) == size;
}

bool RmSerial::send_data(const SendData& data) {
    return send_data((uint8_t*)(&data), sizeof(SendData));
}


void process_data(uint8_t* s, uint8_t* e) {        //参数：头指针，尾指针
    if (e - s != sizeof(McuData)) {
        return;
    }
    McuData mcu_data;
    memcpy(&mcu_data, s, sizeof(McuData));
    if (mcu_data.start_flag != 's') {
        cout<<"Not Starter with 's' "<<endl;
        return;
    }
    receive_mtx.lock();
    readEngineerMcuData(&mcu_data, &g_config_data.start, &g_config_data.state);
    receive_mtx.unlock();
}

void receive_data(RmSerial* rm_serial) {
    static uint8_t buff[100];
    uint8_t* buffer_tail = buff;
    serial::Serial* port = rm_serial->active_port;
    size_t wait_in_buffer;
    port->flush();
    while (rm_serial->thread_running) {
        wait_in_buffer = port->available();
        if (wait_in_buffer) {
            port->read(buffer_tail,1);
            buffer_tail += 1;
            if (buffer_tail[-1] == 'e') {
                *buffer_tail = 0;
                process_data(buff, buffer_tail);
                buffer_tail = buff;
            }
        }
    }
}

//
void RmSerial::start_thread() {
    if (init_success) {
        thread_running = true;
        std::thread task(receive_data, this);
        task.detach();
    }
}

void RmSerial::stop_thread() {
    if (init_success) {
        thread_running = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


bool RmSerial::init() {
    active_port = new Serial(uart_port, 115200,
                             serial::Timeout::simpleTimeout(1000));
    init_success = true;

    //开启数据接受线程
    start_thread();
    if (active_port->isOpen()) {
        cout << "Successfully initialized port " << uart_port;
        return true;
    } else {
        cout << "Failed to initialize port " <<uart_port;
        return false;
    }
}

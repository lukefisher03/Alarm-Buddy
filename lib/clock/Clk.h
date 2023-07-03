#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>


#ifndef CLK_H
#define CLK_H

class Clk{
    private:
        int hours, minutes, seconds, increment_flag, selection_int, meridiem_set;
        std::string time, meridiem;
        int* modes [3] = { &hours, &minutes, &seconds};
        int* selector;
    public:
        Clk();
        Clk(int h, int m, int s);
        void tick();
        void shift();
        void update_time();
        int* change_selector();
        int initiate_increment();
        int set_increment();
        std::string return_time();
        int* return_selector();
        int return_mode();
};

#endif

#pragma once

#include <iostream>
#include <string>



#ifndef CLK_H
#define CLK_H

class Clk{
    private:
        int hours_, minutes_, seconds_, increment_flag_, selection_int_, meridiem_set_;
        std::string time_str_, meridiem_;
        int* modes_ [3] = { &hours_, &minutes_, &seconds_};
        int* selector_;
    public:
        Clk();
        Clk(int h, int m, int s);
        void Tick();
        void Shift();
        bool SetTime(int, int, int);
        bool ValidateTime(int, int, int);
        int* ChangeSelector();
        int InitiateIncrement();
        int SetIncrement();
        std::string get_time_str();
        const char* get_time_c_str();
        int* get_selector();
        int get_mode();
};

#endif

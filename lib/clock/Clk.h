#pragma once

#include <iostream>
#include <string>
#include <list>

#include "../Alarm/Alarm.h"
#include "../common/time_utils.h"

class Clk{
    private:
        ab_time current_time_;
        int increment_flag_, selection_int_;
        std::string time_str_, meridiem_;
        int* modes_ [3] = { &current_time_.hours, &current_time_.minutes, &current_time_.seconds};
        int* selector_;
        std::list<Alarm> alarm_list;
    public:
        Clk();
        Clk(int h, int m, int s);
        void Tick();
        void Shift();
        void CreateAlarm(int, int, int, int);
        bool SetTime(int, int, int);
        bool ValidateTime(int, int, int);
        bool CreateAlarm(ab_time, ab_time);
        int* ChangeSelector();
        int InitiateIncrement();
        int SetIncrement();
        std::string get_time_str();
        const char* get_time_c_str();
        int* get_selector();
        int get_mode();
};
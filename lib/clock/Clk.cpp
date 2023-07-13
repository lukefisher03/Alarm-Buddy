#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <list>

#include "Clk.h"
#include "../Alarm/Alarm.h"
#include "../common/time_utils.h"


Clk::Clk()
    :increment_flag_(1), selection_int_(0), meridiem_("A.M."), selector_(modes_[selection_int_]) {
        current_time_.hours = 12;
        current_time_.minutes = 0;
        current_time_.seconds = 0;
        current_time_.meridiem_flag = 0;
    }

Clk::Clk(int h, int m, int s)  
    :increment_flag_(1), selection_int_(0), meridiem_("A.M."), selector_(modes_[selection_int_]) {
        current_time_.hours = h;
        current_time_.minutes = m;
        current_time_.seconds = s;
        current_time_.meridiem_flag = 0;
    }

void Clk::Tick(){
    // main function to be run during loop() in main.cpp
    std::this_thread::sleep_for(std::chrono::seconds(1));
    current_time_.seconds++;
    Shift();
    
    std::string h_str = std::to_string(current_time_.hours);
    std::string m_str = std::to_string(current_time_.minutes);
    std::string s_str = std::to_string(current_time_.seconds);

    time_str_ = h_str + ":" + m_str + ":" + s_str + " " + meridiem_;
};

void Clk::Shift(){
    // mutator function used to keep each time segment in their respective ranges
    if(current_time_.seconds >= 60){
        current_time_.seconds = 0;
        current_time_.minutes++;
    }
  
    if(current_time_.minutes >= 60){
        current_time_.minutes = 0;
        current_time_.hours++;
      
    }
  
    if(current_time_.hours == 12 && current_time_.minutes == 0 && current_time_.seconds == 0){
        if(current_time_.meridiem_flag == 0){
            meridiem_ = "P.M";
            current_time_.meridiem_flag = 1;
        }
        else{ 
            meridiem_ = "A.M.";
            current_time_.meridiem_flag = 0;
        }
    }
    if(current_time_.hours == 13){
        current_time_.hours = 1;
    }
};

bool Clk::SetTime(int hours, int minutes, int seconds){
    // This mutator function updates the time
    if (!ValidateTime(hours, minutes, seconds)) {
        return false;
    }
    
    current_time_.hours = hours;
    current_time_.minutes = minutes;
    current_time_.seconds = seconds;

    return true;
};

void Clk::CreateAlarm(int h, int m, int s, int m_flag){
    // This mutator function creates a new alarm and adds it to the alarm list, takes a hour, minute, second, and meridiem flag
    ab_time alarm_time;
    alarm_time.hours = h;
    alarm_time.hours = m;
    alarm_time.hours = s;
    alarm_time.meridiem_flag = m_flag;

    Alarm new_alarm = Alarm(current_time_, alarm_time);
    alarm_list.push_back(new_alarm);
};

bool Clk::ValidateTime(int hours, int minutes, int seconds) {
    if (hours > 12 || minutes > 60 || seconds > 60) {
        return false;
    }

    if (hours < 1 || minutes < 0 || seconds < 0) {
        return false;
    }

    return true;
};

int* Clk::ChangeSelector(){
    // This mutator function will be triggered by a button push, change which time segment is
    // being incremented (hours, minutes, or seconds), returns the address the selector is pointing to

    if (selector_ == &current_time_.seconds) {
        selection_int_ = 0;
    } else {
        selection_int_++;
    }
    
    selector_ = modes_[selection_int_];
    
    return selector_;
}; 

int Clk::InitiateIncrement(){
    //This mutator function will be button triggered, increment selected time segment 
    //retuns the current time data segment being edited

    *selector_ = *selector_ + increment_flag_;
    return *selector_;
};

int Clk::SetIncrement(){
    //This  mutator function will be button triggered and set increment type to increase or decrease,
    //returns increment flag
      
    increment_flag_ = increment_flag_ * -1;
    if (increment_flag_ == 1){
        std::cout << "Clock will increase values set";
    }
    else{
        std::cout << "Clock will decrease values selected";
    }

    return increment_flag_;
};

std::string Clk::get_time_str(){
    // accessor fucntion returns the current time string
    return time_str_;
};

const char * Clk::get_time_c_str() {
    // accessor function returns the time string as a c string
    return time_str_.c_str();
};

int* Clk::get_selector(){
    // accessor function returns the current selector address
    return selector_;
};

int Clk::get_mode(){
    // accesssor function , returns which time division is being edited
    return *modes_[selection_int_];
};

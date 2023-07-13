#include "Clk.h"
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>


Clk::Clk()
    : hours_(11), minutes_(59), seconds_(30), increment_flag_(1), selection_int_(0), meridiem_set_(0), meridiem_("A.M."), selector_(modes_[selection_int_]) {}

Clk::Clk(int h, int m, int s)  
    : hours_(h), minutes_(m), seconds_(s), increment_flag_(1), selection_int_(0), meridiem_set_(0), meridiem_("A.M."), selector_(modes_[selection_int_]) {}

void Clk::Tick(){
    // main function to be run during loop() in main.cpp
    std::this_thread::sleep_for(std::chrono::seconds(1));
    seconds_++;
    Shift();
    
    std::string h_str = std::to_string(hours_);
    std::string m_str = std::to_string(minutes_);
    std::string s_str = std::to_string(seconds_);

    time_str_ = h_str + ":" + m_str + ":" + s_str + " " + meridiem_;
};

void Clk::Shift(){
    // mutator function used to keep each time segment in their respective ranges
    if(seconds_ >= 60){
        seconds_ = 0;
        minutes_++;
    }
  
    if(minutes_ >= 60){
        minutes_ = 0;
        hours_++;
      
    }
  
    if(hours_ == 12 && minutes_ == 0 && seconds_ == 0){
        if(meridiem_set_ == 0){
            meridiem_ = "P.M";
            meridiem_set_ = 1;
        }
        else{ 
            meridiem_ = "A.M.";
            meridiem_set_ = 0;
        }
    }
    if(hours_ == 13){
        hours_ = 1;
    }
};

bool Clk::SetTime(int hours, int minutes, int seconds){
    // This mutator function updates the time
    if (!ValidateTime(hours, minutes, seconds)) {
        return false;
    }
    
    hours_ = hours;
    minutes_ = minutes;
    seconds_ = seconds;

    return true;
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

    if (selector_ == &seconds_) {
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

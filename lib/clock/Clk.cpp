#include "Clk.h"

#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

// simple constructor
Clk::Clk(){
    hours_ = 11;
    minutes_ = 59;
    seconds_ = 30;
    selection_int_ = 0;
    meridiem_ = "A.M.";
    meridiem_set_ = 0;
    increment_flag_ = 1;
    selector_ = modes_[selection_int_];
};
        
void Clk::Tick(){
    // main function to be run during loop() in main.cpp

    std::this_thread::sleep_for(std::chrono::seconds(1));
    seconds_++;
    Shift();
    UpdateTime();
};

void Clk::Shift(){
    // mutator function used to keep each time segment in their respective ranges

    if(seconds_ == 60){
        seconds_ = 0;
        minutes_++;
    }
    if(minutes_ == 60){
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

void Clk::UpdateTime(){
    // This mutator function updates the time string

    std::string h_string = std::to_string(hours_);
    std::string m_string = std::to_string(minutes_);
    std::string s_string = std::to_string(seconds_);
    time_str_ = h_string + ":" + m_string + ":" + s_string + " " + meridiem_;
}

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

std::string Clk::GetTime(){
    // accessor fucntion returns the current time string
    return time_str_;
};

int* Clk::GetSelector(){
    // accessor function returns the current selector address
    return selector_;
};

int Clk::GetMode(){
    // accesssor function , returns which time division is being edited
    return *modes_[selection_int_];
};

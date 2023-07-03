#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

#include "Clk.h"


Clk::Clk()
    : hours(11), minutes(59), seconds(30), increment_flag(1), selection_int(0), meridiem_set(0), meridiem("A.M."), selector(modes[selection_int]) {}

Clk::Clk(int h, int m, int s)  
    : hours(h), minutes(m), seconds(s), increment_flag(1), selection_int(0), meridiem_set(0), meridiem("A.M."), selector(modes[selection_int]) {}

void Clk::tick(){
    // main function to be run during loop() in main.cpp
    std::this_thread::sleep_for(std::chrono::seconds(1));
    seconds++;
    shift();
    update_time();
};

void Clk::shift(){
    // mutator function used to keep each time segment in their respective ranges
    if(seconds >= 60){
        seconds = 0;
        minutes++;
    }
    if(minutes >= 60){
        minutes = 0;
        hours++;
    }
    if(hours == 12 && minutes == 0 && seconds == 0){
        if(meridiem_set == 0){
            meridiem = "P.M";
            meridiem_set = 1;
        }
        else{ 
            meridiem = "A.M.";
            meridiem_set = 0;
        }
    }
    if(hours == 13){
        hours = 1;
    }
};

void Clk::update_time(){
    // This mutator function updates the time string
    std::string h_string = std::to_string(hours);
    std::string m_string = std::to_string(minutes);
    std::string s_string = std::to_string(seconds);
    time = h_string + ":" + m_string + ":" + s_string + " " + meridiem;
}

int* Clk::change_selector(){
    /* This mutator function will be triggered by a button push, change which time segment is
    being incremented (hours, minutes, or seconds), returns the address the selector is pointing to */
    if (selection_int == 2){
        selection_int = 0;
    }
    else{
        selection_int++;
    }
    selector = modes[selection_int];
    return selector;
}; 

int Clk::initiate_increment(){
    /* This mutator function will be button triggered, increment selected time segment
    retuns the current time data segment being edited */
    *selector = *selector + increment_flag;
    return *selector;
};

int Clk::set_increment(){
    /* This  mutator function will be button triggered and set increment type to increase or decrease,
    returns increment flag*/
    increment_flag = increment_flag * -1;
    if (increment_flag == 1){
        std::cout << "Clock will increase values set";
    }
    else{
        std::cout << "Clock will decrease values selected";
    }
    return increment_flag;
};

std::string Clk::return_time(){
    // accessor fucntion returns the current time string
    return time;
};

int* Clk::return_selector(){
    // accessor function returns the current selector address
    return selector;
};

int Clk::return_mode(){
    // accesssor function , returns which time division is being edited
    return *modes[selection_int];
};

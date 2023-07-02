#include "Clk.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

        // simple constructor
Clk::Clk(){
    hours = 11;
    minutes = 59;
    seconds = 30;
    selection_int = 0;
    meridiem = "A.M.";
    meridiem_set = 0;
    increment_flag = 1;
    selector = modes[selection_int];
};
        
        // main function to be run during loop() in main.cpp
void Clk::tick(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    seconds++;
    shift();
    update_time();
};

        // mutator function used to keep each time segment in their respective ranges
void Clk::shift(){
    if(seconds == 60){
        seconds = 0;
        minutes++;
    }
    if(minutes == 60){
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

        // This mutator function updates the time string
void Clk::update_time(){
    std::string h_string = std::to_string(hours);
    std::string m_string = std::to_string(minutes);
    std::string s_string = std::to_string(seconds);
    time = h_string + ":" + m_string + ":" + s_string + " " + meridiem;
}

// This mutator function will be triggered by a button push, change which time segment is
// being incremented (hours, minutes, or seconds), returns the address the selector is pointing to
int* Clk::change_selector(){
    if (selection_int == 2){
        selection_int = 0;
    }
    else{
        selection_int++;
    }
    selector = modes[selection_int];
    return selector;
}; 

//This mutator function will be button triggered, increment selected time segment
// retuns the current time data segment being edited
int Clk::initiate_increment(){
    *selector = *selector + increment_flag;
    return *selector;
};

// This  mutator function will be button triggered and set increment type to increase or decrease,
// returns increment flag
int Clk::set_increment(){
    increment_flag = increment_flag * -1;
    if (increment_flag == 1){
        std::cout << "Clock will increase values set";
    }
    else{
        std::cout << "Clock will decrease values selected";
    }
    return increment_flag;
};

// accessor fucntion returns the current time string
std::string Clk::return_time(){
    return time;
};

// accessor function returns the current selector address
int* Clk::return_selector(){
    return selector;
};

// accesssor function , returns which time division is being edited
int Clk::return_mode(){
    return *modes[selection_int];
};

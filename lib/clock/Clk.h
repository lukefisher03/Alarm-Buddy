#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

class Clk{
    private:
        int hours, minutes, seconds, increment_flag, selection_int, meridiem_set;
        std::string time, meridiem;
        int* modes [3] = { &hours, &minutes, &seconds};
        int* selector;
    public:
        // simple constructor
        Clk();
        
        // main function to be run during loop() in main.cpp
        void tick();
        // mutator function used to keep each time segment in their respective ranges
        void shift();

        // This mutator function updates the time string
        void update_time();

        // This mutator function will be triggered by a button push, change which time segment is
        // being incremented (hours, minutes, or seconds), returns the address the selector is pointing to
        int* change_selector();

        //This mutator function will be button triggered, increment selected time segment
        // retuns the current time data segment being edited
        int initiate_increment();

        // This  mutator function will be button triggered and set increment type to increase or decrease,
        // returns increment flag
        int set_increment();

        // accessor fucntion returns the current time string
        std::string return_time();

        // accessor function returns the current selector address
        int* return_selector();

        // accessor function , returns which time division is being edited
        int return_mode();
};

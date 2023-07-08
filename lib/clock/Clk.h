#pragma once

#include <iostream>
#include <string>


class Clk{
    private:
        int hours_, minutes_, seconds_, increment_flag_, selection_int_, meridiem_set_;
        std::string time_str_, meridiem_;
        int* modes_ [3] = { &hours_, &minutes_, &seconds_};
        int* selector_;
    public:
        // simple constructor
        Clk();
        
        // main function to be run during loop() in main.cpp
        void Tick();
        // mutator function used to keep each time segment in their respective ranges
        void Shift();

        // This mutator function updates the time string
        void UpdateTime();

        // This mutator function will be triggered by a button push, change which time segment is
        // being incremented (hours, minutes, or seconds), returns the address the selector is pointing to
        int* ChangeSelector();

        //This mutator function will be button triggered, increment selected time segment
        // retuns the current time data segment being edited
        int InitiateIncrement();

        // This  mutator function will be button triggered and set increment type to increase or decrease,
        // returns increment flag
        int SetIncrement();

        // accessor fucntion returns the current time string
        std::string GetTime();

        // accessor function returns the current selector address
        int* GetSelector();

        // accessor function , returns which time division is being edited
        int GetMode();
};

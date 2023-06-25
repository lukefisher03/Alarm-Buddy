#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


class clk{
    private:
        int hours, minutes, second, increment_flag, selection_int;
        string time, meridiem;
        int* modes [3] = { &hours, &minutes, &second};
        int* selector;
    public:
        // simple constructor
        clk(){
            hours = 12;
            minutes = 59;
            second = 0;
            selection_int = 0;
            meridiem = "A.M.";
            increment_flag = 1;
            selector = modes[selection_int];
        };
        
        // main function to be run during loop() in main.cpp
        void tick(){
            sleep_for(seconds(1));
            second++;
            shift();
            update_time();
        };

        // mutator function used to keep each time segment in their respective ranges
        void shift(){
            if(second == 60){
                second = 0;
                minutes++;
            }
            if(minutes == 60){
                minutes = 0;
                hours++;
            }
            if(hours == 12){
                if(meridiem.compare("P.M") == 0){
                    meridiem = "A.M.";
                }
                else{ 
                    meridiem = "P.M.";
                }
            }
            if(hours == 13){
                hours = 1;
            }
        };

        // mutator function that updates the time string
        void update_time(){
            string h_string = to_string(hours);
            string m_string = to_string(minutes);
            string s_string = to_string(second);
            time = h_string + ":" + m_string + ":" + s_string + " " + meridiem;
        }

        // This mutator function will be triggered by a button push, change which time segment is
        // being incremented (hours, minutes, or seconds)
        void change_selector(){
            if (selection_int == 2){
                selection_int = 0;
            }
            else{
                selection_int++;
            }
            selector = modes[selection_int];
            
        }; 

        //This mutator function will be button triggered, increment selected time segment
        void initiate_increment(){
            *selector = *selector + increment_flag;
        };

        // accessor print function outputs the time (used for testing clock functionality)
        void print_time(){
            cout << time << "\n";
        };
        // accessor print function (test select mode function)
        void print_mode(){
            cout << *modes[selection_int] << "\n";
        };

        // This  mutator function will be button triggered and set increment type to increase or decrease
        void set_increment(){
            increment_flag = increment_flag * -1;
            if (increment_flag == 1){
                cout << "Clock will increase values set";
            }
            else{
                cout << "Clock will decrease values selected";
            }
        };

};
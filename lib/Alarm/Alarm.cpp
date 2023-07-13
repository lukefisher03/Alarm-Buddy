#include <string>

#include "Alarm.h"
#include "../Clock/Clk.h"
#include "../common/time_utils.h"

Alarm::Alarm(ab_time start_time, ab_time set_time)
        {
            Setup(start_time, set_time);
        }

bool Alarm::Setup(ab_time start_time, ab_time set_time){
    // not sure of a better way to do this with these data structs at the moment, maybe future time_utils function?
    current_time_.hours = start_time.hours;
    current_time_.minutes = start_time.minutes;
    current_time_.seconds = start_time.seconds;
    current_time_.meridiem_flag = start_time.meridiem_flag;

    alarm_time_.hours = set_time.hours;
    alarm_time_.minutes = set_time.minutes;
    alarm_time_.seconds = set_time.seconds;
    alarm_time_.meridiem_flag = set_time.meridiem_flag;
};

bool Alarm::CompareTimes(){
    if((current_time_.hours == alarm_time_.hours) && (current_time_.minutes == alarm_time_.minutes)){
        if((current_time_.seconds == alarm_time_.seconds) && (current_time_.meridiem_flag == alarm_time_.meridiem_flag)){
            return true;
        }
    }
    return false;
};

bool Alarm::IncrementTime(){
    current_time_.seconds++;
    if (current_time_.seconds >= 60){
        current_time_.seconds = 0;
        current_time_.minutes++;
    }
    if (current_time_.minutes >= 60){
        current_time_.minutes = 0;
        current_time_.hours++;
    }
    if (current_time_.minutes >= 60){
        current_time_.hours++;
    }
    if(current_time_.hours == 12 && current_time_.minutes == 0 && current_time_.seconds == 0){
        if(current_time_.meridiem_flag == 0){
            current_time_.meridiem_flag = 1;
        }
        else{ 
            current_time_.meridiem_flag = 0;
        }
    }
    if(current_time_.hours == 13){
        current_time_.hours = 1;
    }
};


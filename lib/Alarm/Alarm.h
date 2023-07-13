#pragma once

#include <string>
#include "../common/time_utils.h"
class Alarm{
    private:
        ab_time current_time_, alarm_time_; // ab_time structs for the hours minutes seconds breakdown
    public: 
        Alarm(ab_time start_time, ab_time alarm_time);
        bool Setup(ab_time start_time, ab_time alarm_time);
        bool CompareTimes();
        bool IncrementTime();

};
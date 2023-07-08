#include "clk.h"

int main(){
    Clk test;

    while (true)
    {
        test.Tick();
        printf(test.get_time_c_str());
        printf("\n");
    }
    
};
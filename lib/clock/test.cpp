#include "clk.h"

int main(){
    Clk test;

    while (true)
    {
        test.Tick();
        printf(test.GetTime().c_str());
        printf("\n");
    }
    
};
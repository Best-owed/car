#include "carOpenApi.hpp"
#include "temperature.hpp"
#include "driver.hpp"
#include <bits/stdc++.h>
using namespace std;


int main() {
    if(wiringPiSetupGpio() < 0){
        printf("启动树莓派BCM失败...");
        exit(1);
    }
    auto impl = app::CarImpl();
    auto temp = app::Temperature();
    auto dirv = app::Driver();
    //  impl.setLight(true);
    // delay(1000); // 延时1秒
    //  impl.setLight(false);

    // // impl.setRing(true);
    // delay(2000); // 延时2秒
    // impl.setRing(false);

    // impl.setLedNowTime();
    // while (1)
    // { 
    //     TempNumbers tem = temp.gettemp();
    //     impl.setLedTemp(tem.num0, tem.num1, tem.num2, tem.num3, 1);

    // }
    
    
    while (1)
    {
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            dirv.run();
            break;
        case 2:
            dirv.back();
            break;
        case 3:
            dirv.stop();
            break;
        case 4:
            dirv.turnLeft();
            break;
        case 5:
            dirv.turnRight();
            break;
               
        }
    }
    
     


    
    return 0;
}
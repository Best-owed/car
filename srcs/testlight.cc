#include "carOpenApi.hpp"
#include "temperature.hpp"

#define m1 21
#define m2 20



int main() {
    if(wiringPiSetupGpio() < 0){
        printf("启动树莓派BCM失败...");
        exit(1);
    }
    auto impl = app::CarImpl();
    auto temp = app::Temperature();

    // impl.setLight(true);
    // delay(1000); // 延时1秒
    // impl.setLight(false);

    // // impl.setRing(true);
    // delay(2000); // 延时2秒
    // impl.setRing(false);

    // impl.setLedNowTime();
    while (1)
    { 
        TempNumbers tem = temp.gettemp();
        impl.setLedTemp(tem.num0, tem.num1, tem.num2, tem.num3, 1);

    }
    

    

    // pinMode(m1,OUTPUT);
    // pinMode(m2,OUTPUT);
    // digitalWrite(m1,0);
    // digitalWrite(m2,0);
    // while (1)
    // {
    //     digitalWrite(m1,1);
    //     digitalWrite(m2,0);
    //     sleep(10);
    //     digitalWrite(m1,0);
    //     digitalWrite(m2,1);
    //     sleep(10);
    // }
    
    
    return 0;
}
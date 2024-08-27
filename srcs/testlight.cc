#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>

#define LED_R 23
#define BEEP 17  
#define CLK 22
#define DIO 27
#include "carOpenApi.hpp"


int main() {

    wiringPiSetup();
    wiringPiSetupGpio();
    auto impl = app::CarImpl();
    // impl.setLight(true);
    delay(1000); // 延时1秒
    impl.setLight(true);

    // impl.setRing(true);

    delay(2000); // 延时2秒
    impl.setLight(false);
    impl.setRing(false);

    impl.setLedNumber(10);


    return 0;
}
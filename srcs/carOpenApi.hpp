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
char num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0-9
char numdp[10] = {0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef}; // 小数点
namespace app {
class CarImpl {
  public:
    void setNumber(int x) {
    }
    void setLight(bool mode){
        pinMode(LED_R,OUTPUT);
        if (mode) {
            digitalWrite(LED_R,HIGH);//点亮
        } else {
            digitalWrite(LED_R,LOW);//熄灭
        }
    }
    void setRing(int mode){

        pinMode(BEEP,OUTPUT);
        if(mode){
            digitalWrite(BEEP,HIGH);
        }else{
            digitalWrite(BEEP,LOW);//熄灭
        }
    }

    
    void setLedNumber(int num){
        pinMode(CLK,OUTPUT);
        pinMode(DIO,OUTPUT);
        
        int flag = 1; // 1: 显示小数点 0: 不显示小数点
        // 获取当前时间
        time_t t;
        int timescale[4] = {0, 0, 0, 0};
        struct tm *tm;
        while (1) {
            time(&t);
            tm = localtime(&t);
            timescale[0] = tm->tm_hour / 10;
            timescale[1] = tm->tm_hour % 10;
            timescale[2] = tm->tm_min / 10;
            timescale[3] = tm->tm_min % 10;
            timeDisplay(timescale[0], timescale[1], timescale[2], timescale[3], flag);
            sleep(1);
            flag = !flag;
        }

    }
    
  private:
    char segdata[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x6f};

    void start() {
        digitalWrite(CLK, 1);
        usleep(140);
        digitalWrite(DIO, 1);
        usleep(140);
        digitalWrite(DIO, 0);
        usleep(140);
        digitalWrite(CLK, 0);
        usleep(140);
    }

    void stop() {
        digitalWrite(CLK, 0);
        usleep(140);
        digitalWrite(DIO, 0);
        usleep(140);
        digitalWrite(CLK, 1);
        usleep(140);
        digitalWrite(DIO, 1);
        usleep(140);
    }

    void writeBit(char bit) {
        digitalWrite(CLK, 0);
        usleep(140);
        digitalWrite(DIO, bit);
        usleep(140);
        digitalWrite(CLK, 1);
        usleep(140);
    }

    void writeByte(char data) {
        char i = 0;
        for (i = 0; i < 8; i++) {
            writeBit((data >> i) & 0x01);
        }
        digitalWrite(CLK, 0);
        usleep(140);
        digitalWrite(DIO, 1);
        usleep(140);
        digitalWrite(CLK, 1);
        usleep(140);
        pinMode(DIO, INPUT);
        while(digitalRead(DIO));
        pinMode(DIO, OUTPUT);
    }

    void writeCommand(char command) {
        start();
        writeByte(command);
        stop();
    }

    void writeData(char addr, char data) {
        start();
        writeByte(addr);
        writeByte(data);
        stop();
    }

    void timeDisplay(int i, int j, int k, int l, int flag) {
        writeCommand(0x40); // 写入数据
        writeCommand(0x44); // 位置设置
        writeData(0xc0, num[i]);
        if (flag) {
            writeData(0xc1, numdp[j]);
        }else {
            writeData(0xc1, num[j]);
        }
        writeData(0xc2, num[k]);
        writeData(0xc3, num[l]);
        writeCommand(0x88); // 打开显示
    }
};

}
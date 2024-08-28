#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#define DATA 13 

struct TempNumbers{
    int num0; //湿度十位
    int num1; //湿度个位
    int num2; //温度十位
    int num3; //温度个位
};


namespace app {

class Temperature {
  public:

    TempNumbers gettemp(){
        

        pinMode(DATA,OUTPUT);
        delayMicroseconds(140);
        digitalWrite(DATA,HIGH);
        delayMicroseconds(140);
        digitalWrite(DATA,LOW);
        delay(18);
        digitalWrite(DATA,HIGH);
        delayMicroseconds(40);
    
        pinMode(DATA,INPUT);
        TempNumbers tempnums = {0};
        if (digitalRead(DATA) == LOW)
        {
            while (digitalRead(DATA) == LOW);
            while (digitalRead(DATA) == HIGH);
            int data[5] = {};
            for (int i = 0; i < 5; i++)
            {
                data[i] = write_byte();
                if(data[i] < 0){
                    printf("超时\n");
                    break;
                }
            }
            int sum = data[0]+ data[1]+ data[2]+ data[3];
            
            tempnums.num0 = data[0];
            tempnums.num1 = data[1];
            tempnums.num2 = data[2];
            tempnums.num3 = data[3];
            if(data[4] == sum){
                
                printf("湿度:%d.%d %%RH\n",data[0],data[1]);
                printf("温度:%d.%d℃ \n",data[2],data[3]);
            }else{
                printf("校验错误\n");
            }
        }else{
            printf("未响应\n");
        }

        sleep(1);
        printf("=============\n");

        return tempnums;
    
    
    
    }
    


  private:


    int write_bit(){
        //digitalWrite(DATA,LOW);
        while (digitalRead(DATA) == LOW);

        delayMicroseconds(28);
        if(digitalRead(DATA) == HIGH){
            time_t t1 = time(NULL);

            while(digitalRead(DATA) == HIGH)
            {
                time_t t2 = time(NULL);
                if(t2 - t1 >= 1){
                    return -1;
                }

            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int write_byte(){
        int byte = 0;
        for (int i = 0; i < 8; i++)
        {
            int ret = write_bit();
            if(ret >= 0){
                byte <<= 1;
                byte |= ret;

            }else {
                return -1;
            }
        }
        return byte;
    }

};

}
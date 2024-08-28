#include <wiringPi.h>
#include <time.h>

#define DATA 26

int write_bit(){
    while (digitalWrite(DATA,LOW));
    delayMicroseconds(28);
    if(digitalRead(DATA == HIGH)){
        time_t t1 = time(NULL);

    
        while (digitalRead(DATA) == HIGH)
        {
            time_t t2 = time(NULL);
            if(t2 - t1 >= 1){
                return -1;
            }

        }
        return 1;
    }else return 0;
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

int main(){

    
    pinMode(DATA,OUTPUT);
    dalayMucrisecinds(140);
    digitalWrite(DATA,HIGH);
    dalayMucrisecinds(140);
    digitalWrite(DATA,LOW);
    dalay(18);
    digitalWrite(DATA,HIGH);
    dalayMucrisecinds(40);

    pinMode(DATA,INPUT);
    if (digitalRead(DATA) == LOW)
    {
        while (digitalRead(DATA) == LOW);
        while (digitalRead(DATA) == HIGH);
        int data[5] = {};
        for (int i = 0; i < 5; i++)
        {
            data[i] = write_byte();
            if(data[i] < 0){
                print("超时\n");
                break;
            }
        }
        int sum = data[0]+ data[1]+ data[2]+ data[3];
        if(data[4]== sum){
            printf("湿度:%d.%d %%RH\n",data[0],data[1]);
            printf("温度:%d.%d℃ \n",data[2],data[3]);
        }else{
            printf("校验错误\n");
        }
    }else{
        printf("未响应\n");
    }
    
}
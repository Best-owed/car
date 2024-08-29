#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <softPwm.h>

#define PWM_L 24
#define PWM_R 25
#define M1 21
#define M2 20
#define M3 16
#define M4 12


namespace app {

class Driver {
  public:
    Driver() {
      init(); // 在构造函数中初始化，只调用一次
    }
    
    void back() {
      softPwmWrite(PWM_L, 10);
      softPwmWrite(PWM_R, 10);
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
      digitalWrite(M3, HIGH);
      digitalWrite(M4, LOW);
    }

    void run() {
      softPwmWrite(PWM_L, 100);
      softPwmWrite(PWM_R, 100);
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
      digitalWrite(M3, LOW);
      digitalWrite(M4, HIGH);
    }

    void stop() {
      softPwmWrite(PWM_L, 0);
      softPwmWrite(PWM_R, 0);
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      digitalWrite(M3, LOW);
      digitalWrite(M4, LOW);
    }

    void turnLeft() {
      softPwmWrite(PWM_L, 10);
      softPwmWrite(PWM_R, 50);
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
      digitalWrite(M3, LOW);
      digitalWrite(M4, HIGH);
      delay(500); // 向左转500毫秒
      stop(); // 转弯后停止
    }

    void turnRight() {
      softPwmWrite(PWM_L, 50);
      softPwmWrite(PWM_R, 10);
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
      digitalWrite(M3, HIGH);
      digitalWrite(M4, LOW);
      delay(500); // 向右转500毫秒
      stop(); // 转弯后停止
    }

  private:
    void init() {
      softPwmCreate(PWM_L, 0, 100);
      softPwmCreate(PWM_R, 0, 100);
      pinMode(M1, OUTPUT);
      pinMode(M2, OUTPUT);
      pinMode(M3, OUTPUT);
      pinMode(M4, OUTPUT);
    }
};

}
#include <Wire.h>   
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 530

int servoIndex = 5;
int home45 = map(45,0,180,SERVOMIN,SERVOMAX);

void setup() {
    Serial.begin(115200);
    pwm.begin();
    pwm.setPWMFreq(50);

    for(int i=0;i<=servoIndex;i++){
        pwm.setPWM(i,0,home45);
    }
}

void loop() {
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();
    if(currentTime-lastTime >= 100) {
        if (Serial.available()){
            String ReadData = Serial.readStringUntil('/n');
            ReadData.trim();
            if (ReadData == "Ping") {
                Serial.print("Ping");
            }
            else if (ReadData.startsWith("s1") || ReadData.startsWith("s2") || ReadData.startsWith("s3") || ReadData.startsWith("s4") || ReadData.startsWith("s5") || ReadData.startsWith("s6")){
                String servo = ReadData.substring(0,2);
                int ang = ReadData.substring(2).toInt();
                movePositive(servo,ang);
            }
            else if (ReadData.startsWith("rs1") || ReadData.startsWith("rs2") || ReadData.startsWith("rs3") || ReadData.startsWith("rs4") || ReadData.startsWith("rs5") || ReadData.startsWith("rs6")){
                String servo = ReadData.substring(0,3);
                int ang=ReadData.substring(3).toInt();
                moveNegative(servo,ang);
            }else if (ReadData.toInt() <= 17) {
                int arm = ReadData.substring(0,1).toInt();
                int s1 = ReadData.substring(1,4).toInt();
                int s2 = ReadData.substring(4,7).toInt();
                int s3 = ReadData.substring(7,10).toInt();
                int s4 = ReadData.substring(10,13).toInt();
                int s5 = ReadData.substring(13,16).toInt();
                moveToPosition(arm, s1, s2, s3, s4, s5);
            }
            else if (ReadData == "end") {
                Serial.print("End");
            }
        }
    }
}

void moveToPosition(int arm, int s1, int s2, int s3, int s4, int s5){
    int ang1 = map(s1, 0 180, SERVOMIN, SERVOMAX);
    int ang2 = map(s2, 0 180, SERVOMIN, SERVOMAX);
    int ang3 = map(s3, 0 180, SERVOMIN, SERVOMAX);
    int ang4 = map(s4, 0 180, SERVOMIN, SERVOMAX);
    int ang5 = map(s5, 0 180, SERVOMIN, SERVOMAX);

    pwm.setPWM(0,0,ang1);
    pwm.setPWM(1,0,ang2);
    pwm.setPWM(2,0,ang3);
    pwm.setPWM(3,0,ang4);
    pwm.setPWM(4,0,ang5);

    Serial.print("\n");
    Serial.print("Success");
}

void movePositive(String data, int ang){
    int move = map(ang,0,180,SERVOMIN,SERVOMAX);
    if (data == "s1"){
        pwm.setPWM(0,0,move);
        Serial.print("done");
    }
    else if (data == "s2"){
        pwm.setPWM(1,0,move);
        Serial.print("done");
    }
    else if (data == "s3"){
        pwm.setPWM(2,0,move);
        Serial.print("done");
    }
    else if (data == "s4"){
        pwm.setPWM(3,0,move);
        Serial.print("done");
    }
    else if (data == "s5"){
        pwm.setPWM(4,0,move);
        Serial.print("done");
    }
    else if (data == "s6"){
        pwm.setPWM(5,0,move);
        Serial.print("done");
    }
}

void moveNegative(String data, int ang){
    int move = map(-ang,0,180,SERVOMIN,SERVOMAX);
    if (data == "rs1"){
        pwm.setPWM(0,0,move);
        Serial.print("done");
    }
    else if (data == "rs2"){
        pwm.setPWM(1,0,move);
        Serial.print("done");
    }
    else if (data == "rs3"){
        pwm.setPWM(2,0,move);
        Serial.print("done");
    }
    else if (data == "rs4"){
        pwm.setPWM(3,0,move);
        Serial.print("done");
    }
    else if (data == "rs5"){
        pwm.setPWM(4,0,move);
        Serial.print("done");
    }
    else if (data == "rs6"){
        pwm.setPWM(5,0,move);
        Serial.print("done");
    }
}
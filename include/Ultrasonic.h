#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic
{
private:
    int _trigPin;
    int _echoPin;
    long _duration;
    long _distance;
    int _state;
    void readSensor();
public:
    enum STATE
        {
            FAR,
            CLOSE,
            NO_POS
        };
    Ultrasonic();
    Ultrasonic(int trigPin, int echoPin);
    void Begin();
    void sensorCallBack();
    int getState();
};

#endif
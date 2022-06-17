#include <Arduino.h>
#include "Ultrasonic.h"


Ultrasonic::Ultrasonic(int trigPin, int echoPin){
    _trigPin = trigPin;
    _echoPin = echoPin;
    _state = NO_POS;
}
Ultrasonic::Ultrasonic(){
    _trigPin = 2;
    _echoPin = 3;
    _state = NO_POS;
}

int Ultrasonic::getState(){
    return _state;
}

void Ultrasonic::Begin(){
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

void Ultrasonic::readSensor(){
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    _duration = pulseIn(_echoPin, HIGH);
    _distance = _duration / 58;
}

void Ultrasonic::sensorCallBack(){
    readSensor();
    if(_distance < 38 && _distance > 3){
        if(_distance < 18){
            _state = CLOSE;
        } else{
            _state = FAR;
        }
    }
    _state = NO_POS;
}
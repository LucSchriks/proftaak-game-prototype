#include <Arduino.h>
#include "playingField.h"
#include "Ultrasonic.h"

playingField::playingField()
{
    Ultrasonic sensor1(3, 4);
    Ultrasonic sensor2(5, 6);
}

void playingField::Init()
{
    sensor1.Begin();
    sensor2.Begin();
}

int playingField::getFieldPos(){
    return _fieldPosition;
}

void playingField::fieldCallBack()
{
    sensor1.sensorCallBack();
    sensor2.sensorCallBack();
    _sensor1State = sensor1.getState();
    _sensor2State = sensor2.getState();
    if(_sensor1State == Ultrasonic::CLOSE && _sensor2State == Ultrasonic::NO_POS){
        _fieldPosition = BOTTOM_LEFT;
    }else if(_sensor1State == Ultrasonic::NO_POS && _sensor2State == Ultrasonic::CLOSE){
        _fieldPosition = BOTTOM_RIGHT;
    }else if(_sensor1State == Ultrasonic::FAR && _sensor2State == Ultrasonic::NO_POS){
        _fieldPosition = TOP_LEFT;
    }else if(_sensor1State == Ultrasonic::NO_POS && _sensor2State == Ultrasonic::FAR){
        _fieldPosition = TOP_RIGHT;
    }else{
        _fieldPosition = NONE;
    }
}
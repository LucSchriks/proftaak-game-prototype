#ifndef playingField_h
#define playingField_h

#include "Arduino.h"
#include "Ultrasonic.h"

class playingField
{
private:
    int _fieldPosition;
    int _sensor1State = NONE;
    int _sensor2State = NONE;
    Ultrasonic sensor1;
    Ultrasonic sensor2;
public:
    enum POSITION
        {
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT,
            NONE
        };
    playingField();
    void Init();
    void fieldCallBack();
    int getFieldPos();
};

#endif
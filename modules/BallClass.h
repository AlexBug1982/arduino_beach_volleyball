#ifndef _BALL_H      //tells compiler to compile this class only once 
#define _BALL_H 

#include "Arduino.h"
class Ball {
    private:
        const CRGB _color = 0xFFFF00;
        const byte bounderies[4] = {0,17,0,8};

    protected:
        byte _startX;
        byte _startY;
        byte _destinationX;
        byte _destinationY;
        byte _currentX;
        byte _currentY;
    public:
        //virtual ~Player(){};
        Ball();
        void setStartPosition(byte x, byte y);
        void setDestinationPosition(byte x, byte y);
        byte getStartX();
        byte getStartY();
        byte getDestinationX();
        byte getDestinationY();
        byte getCurrentX();
        byte getCurrentY();
        CRGB getColor();
        void fly();
};

// Member functions definitions including constructor
Ball::Ball() {
}

void Ball::setStartPosition(byte startX, byte startY) {
    _startX = startX;
    _currentX = startX;
    _startY = startY;
    _currentY = startY;
}

byte Ball::getStartX(void) {
    return _startX;
}

byte Ball::getStartY(void) {
    return _startY;
}

byte Ball::getDestinationX(void) {
    return _destinationX;
}

byte Ball::getDestinationY(void) {
    return _destinationY;
}

byte Ball::getCurrentX(void) {
    return _currentX;
}

byte Ball::getCurrentY(void) {
    return _currentY;
}

CRGB Ball::getColor(void) {
    return _color;
}

void Ball::fly(void){
    
}

#endif

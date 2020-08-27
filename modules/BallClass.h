#ifndef _BALL_H      //tells compiler to compile this class only once 
#define _BALL_H 

#include "Arduino.h"


class Ball {
    private:
        const CRGB _color = 0xFFFF00;
        const byte bounderies[4] = {0,17,0,8};
        bool hasDestiantionToFlyTo;
        byte FIELD_LENGTH;
        byte FIELD_HEIGHT;

        Position *startPosition;
        Position *currentPosition;
        Position *destinationPosition;
        //byte flightPath[];
        void calculateFlightPath(void);
    public:
        //virtual ~Player(){};
        Ball(byte l, byte h);
        void setStart(byte x, byte y);
        void setDestination(byte x, byte y);
        void setRandomDestination(bool serve_from_blue_team);
        Position getStart(void);
        Position getDestination(void);
        Position getCurrent(void);
        CRGB getColor();
        void fly();
};

// Member functions definitions including constructor
Ball::Ball(byte l, byte h) {
    hasDestiantionToFlyTo = false;
    FIELD_LENGTH = l;
    FIELD_HEIGHT = h;
    this->startPosition = new Position(0,0);
    this->currentPosition = new Position(0,0);
    this->destinationPosition = new Position(0,0);
}

void Ball::setStart(byte x, byte y) {
    this->startPosition->setX(x);
    this->startPosition->setY(y);
    this->currentPosition->setX(x);
    this->currentPosition->setY(y);
}

Position Ball::getStart(void) {
    return startPosition;
}

void Ball::setDestination(byte x, byte y) {
    this->destinationPosition->setX(x);
    this->destinationPosition->setY(y);
}

Position Ball::getDestination(void) {
    return destinationPosition;
}

Position Ball::getCurrent(void) {
    return currentPosition;
}

CRGB Ball::getColor(void) {
    return _color;
}

void Ball::fly(){
    if (hasDestiantionToFlyTo){
        
    }
}

void Ball::setRandomDestination(bool serve_from_blue_team) {
    if (hasDestiantionToFlyTo == true) {
        return;
    }
    byte randomDestinationX = 0;
    byte randomDestinationY = 0;
    if (serve_from_blue_team) {
        randomDestinationX =  byte(
                            random(
                                FIELD_LENGTH/2, 
                                FIELD_LENGTH
                                )
                            );
         randomDestinationY = byte(
                            random(
                                0, 
                                FIELD_HEIGHT
                                )
                            );
    } else {
        randomDestinationX = byte(
                            random(
                                0, 
                                FIELD_LENGTH/2
                                )
                            ); 
         randomDestinationY = byte(
                            random(
                                0, 
                                FIELD_HEIGHT
                                )
                            );
    }
    destinationPosition->setX(randomDestinationX);
    destinationPosition->setY(randomDestinationY);
    calculateFlightPath();
    hasDestiantionToFlyTo = true;
}

void Ball::calculateFlightPath() {
    Serial.print("destination: ");
    Serial.println(getDestination().toString());
    Serial.print("current: ");
    Serial.println(getCurrent().toString());
    byte diffX = abs(getDestination().getX() - getCurrent().getX());
    Serial.print("diffX: ");
    Serial.println(diffX);
    byte diffY = abs(getDestination().getY() - getCurrent().getY());
    Serial.print("diffY: ");
    Serial.println(diffY);
    byte flightPoints = max(diffX, diffY);
    Serial.print("flightPoints: ");
    Serial.println(flightPoints);

    float xToYRation;
    if (diffX == 0 || diffY == 0) {
        xToYRation = 0;
    } else if (diffX > diffY) {
        xToYRation = float(diffX) / float(diffY);
    } else {
        xToYRation = float(diffY) / float(diffX);
    }
    Serial.print("xToYRation: ");
    Serial.println(xToYRation);

    byte flightPath[flightPoints][2];
    for(byte flightPointIndex = 0; flightPointIndex < flightPoints; flightPointIndex++) {
        byte flightPoint[2] = {0,1};
        //flightPath[flightPointIndex] = flightPoint;
    }
}

#endif

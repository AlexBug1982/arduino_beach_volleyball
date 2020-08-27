#ifndef _POSITION_H      //tells compiler to compile this class only once 
#define _POSITION_H 

#include "Arduino.h"

class Position {
    private:
        byte x;
        byte y;

    public:
        Position(byte x, byte y) {
            this->x = x;
            this->y = y;
        };
        byte getX() {
            return this->x;
        }
        byte getY() {
            return this->y;
        }
        void setX(byte x) {
            this->x = x;
        }
        void setY(byte y) {
            this->y = y;
        }

        char toString() {
            return char(this->x) + ' ' + char(this->y);
        }

        bool compare(Position p) {
            return this->getX() == p.getX() && this->getY() == p.getY();
        }
};

#endif

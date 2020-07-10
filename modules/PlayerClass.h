#ifndef _PLAYER_H      //tells compiler to compile this class only once 
#define _PLAYER_H 

#include "Arduino.h"
class Player {
    private:
        byte *_bounderies;

    protected:
        byte _x;
        byte _y;
        CRGB _color;
        Player *_teamPlayer;
        void setPosition(byte x, byte y);
        void setMovementBounderis(byte *bounderies);
    public:
        //virtual ~Player(){};
        Player();
        byte getX();
        byte getY();
        CRGB getColor();
        void move();
        void setTeamPlayer(Player *teamPlayer);
};

// Member functions definitions including constructor
Player::Player() {
}

void Player::setTeamPlayer(Player *teamPlayer) {
    _teamPlayer = teamPlayer;
}

void Player::setPosition(byte x, byte y) {
    _x = x;
    _y = y;
}

void Player::setMovementBounderis(byte *bounderies) {
    _bounderies = bounderies;
}

byte Player::getX(void) {
    return _x;
}

byte Player::getY(void) {
    return _y;
}

CRGB Player::getColor(void) {
    return _color;
}

void Player::move(void){
    byte left = _bounderies[0];
    byte right = _bounderies[1];
    byte top = _bounderies[2];
    byte bottom = _bounderies[3];
    //Serial.println("Bounderies");
    //Serial.println(left);
    //Serial.println(right);
    //Serial.println(top);
    //Serial.println(bottom);

    byte prepXOne = _x;
    byte prepXTwo = _x;
    byte newX = byte(random(prepXOne - 1, prepXTwo + 2));
    if (newX < left) {
        //Serial.println("X too low");
        //Serial.println(newX);
        //Serial.println("---");
        newX = _x; 
    }
    if (newX > right) {
        //Serial.println("X too high");
        //Serial.println(newX);
        //Serial.println("---");
        newX = _x;
    }
    
    byte prepYOne = _y;
    byte prepYTwo = _y;
    byte newY = byte(random(prepYOne - 1, prepYTwo + 2));
    if (newY < top) {
        //Serial.println("Y too low");
        //Serial.println(newY);
        //Serial.println("---");
        newY = _y;
    }
    if (newY > bottom) {
        //Serial.println("Y too high");
        //Serial.println(newY);
        //Serial.println("---");
        newY = _y;
    }
    Player::setPosition(newX, newY);
    //Serial.println("New position");
    //Serial.print("X: ");
    //Serial.println(Player::_x);
    //Serial.print("Y: ");
    //Serial.println(Player::_y);
}

#endif

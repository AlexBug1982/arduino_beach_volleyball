#ifndef _PLAYER_H      //tells compiler to compile this class only once 
#define _PLAYER_H 

#include "Arduino.h"
#include "PositionClass.h"

class Player {
    private:
        byte *_bounderies;
        Position *position;

    protected:
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
    position = new Position(0,0);
    //Position p(0,0);
    //position = &p;
}

void Player::setTeamPlayer(Player *teamPlayer) {
    _teamPlayer = teamPlayer;
}

void Player::setPosition(byte x, byte y) {
    position->setX(x);
    position->setY(y);
}

void Player::setMovementBounderis(byte *bounderies) {
    _bounderies = bounderies;
}

byte Player::getX(void) {
    return position->getX();
}

byte Player::getY(void) {
    return position->getY();
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

    byte prepXOne = position->getX();
    byte prepXTwo = position->getX();
    byte newX = byte(random(prepXOne - 1, prepXTwo + 2));
    if (newX < left) {
        //Serial.println("X too low");
        //Serial.println(newX);
        //Serial.println("---");
        newX = position->getX(); 
    }
    if (newX > right) {
        //Serial.println("X too high");
        //Serial.println(newX);
        //Serial.println("---");
        newX = position->getX();
    }
    
    byte prepYOne = position->getY();
    byte prepYTwo = position->getY();
    byte newY = byte(random(prepYOne - 1, prepYTwo + 2));
    if (newY < top) {
        //Serial.println("Y too low");
        //Serial.println(newY);
        //Serial.println("---");
        newY = position->getY();
    }
    if (newY > bottom) {
        //Serial.println("Y too high");
        //Serial.println(newY);
        //Serial.println("---");
        newY = position->getY();
    }
    Player::setPosition(newX, newY);
    //Serial.println("New position");
    //Serial.print("X: ");
    //Serial.println(Player::_x);
    //Serial.print("Y: ");
    //Serial.println(Player::_y);
}

#endif

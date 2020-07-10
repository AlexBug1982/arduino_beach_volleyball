#ifndef _REDPLAYER_H      //tells compiler to compile this class only once 
#define _REDPLAYER_H 

#include "Arduino.h"
#include "PlayerClass.h"

class RedPlayer:public Player {
    private:
        const CRGB red_color = 0xFF0000;
        const byte bounderies[4] = {9,16,1,7};
    public:
        RedPlayer(byte x, byte y);
};

// Member functions definitions including constructor
RedPlayer::RedPlayer(byte x, byte y) {
    Player::_color = red_color;
    Player::setPosition(x,y);
    Player::setMovementBounderis(bounderies);
}


#endif
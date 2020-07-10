#ifndef _BLUEPLAYER_H      //tells compiler to compile this class only once 
#define _BLUEPLAYER_H 

#include "Arduino.h"
#include "PlayerClass.h"

class BluePlayer:public Player {
    private:
        const CRGB blue_color = 0x1E90FF;
        const byte bounderies[4] = {1,8,1,7};

    public:
        BluePlayer(byte x, byte y);
};

// Member functions definitions including constructor
BluePlayer::BluePlayer(byte x, byte y) {
    Player::_color = blue_color;
    Player::setPosition(x,y);
    Player::setMovementBounderis(bounderies);
}

#endif

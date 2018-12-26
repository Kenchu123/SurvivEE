#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Player : public Obj {
    private:
        std::string _name;
        double _moveVel; // move velocity
        double _dirX, _dirY; // player velocity & direct
        double _rotVel; // rotate velocity
        double _deg; // rotate angle
        double _playerX; // player posX, not _posX, which referred to the image center
        double _playerY; // player posY
        int _state; // condition
    public:
        Player();
        ~Player();
        void setInitailPosition(int, int);
        void handleKeyInput(SDL_Event&);
        void move();
        void rotate();
        void collideWall();
        void collideItem();
        void collideOhterPlayer();
        void update();
        void renderPlayer();
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Player : public Obj {
    private:
        std::string _name;
        double _moveVel; // move velocity
        double _dirX, _dirY; // player velocity & direct
        double _rotVel; // rotate velocity
        SDL_Point _rotCenter; // rotate center
        double _deg; // rotate angle
        double _playerX; // player posX, not _posX, which referred to the image left-up point
        double _playerY; // player posY
        double _playerSize; // getWidth() / 2
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
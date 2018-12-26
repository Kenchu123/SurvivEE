#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Player : public Obj {
    private:
        std::string _name;
        double _moveVel; // move velocity
        double _velX, _velY; // player velocity & direct
        double _rotVel; // rotate velocity
        double _deg;
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
#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Bullet;

enum PlayerState {
    alive, dead
};

class Player : public Obj {
    private:
        std::string _name;
        std::string _playerID;
        PlayerType _playerType;
        double _moveVel; // move velocity
        double _dirX, _dirY; // player velocity & direct
        double _rotVel; // rotate velocity
        SDL_Point _rotCenter; // rotate center
        double _deg; // rotate angle
        double _playerX; // player position, not _posX, which referred to the image left-up point
        double _playerY; // player posY
        double _playerSize; // getWidth() / 2
        PlayerState _state; // condition

        double _hp; // HP
        double _defend; // defend coefficient
    public:
        friend class Bullet;

        Player(std::string id = "");
        ~Player();
        void setInitialPosition(int, int);
        void handleKeyInput(SDL_Event&);
        void move();
        void rotate();
        bool collideWall();
        bool collideOtherPlayer();
        void collideItem();
        void update();
        void fire();
        void isShooted(Bullet*);
};

extern std::vector<Player*> players;

#endif
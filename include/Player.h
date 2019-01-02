#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Bullet;

enum PlayerState {
    alive, dead
};

class Player : public Obj {
    protected:
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
        friend class Item;

        Player(std::string id = "");
        ~Player();
        void setInitialPosition(int, int);
        virtual void handleKeyInput(SDL_Event&);
        void move();
        void rotate();
        bool collideWall();
        bool collideOtherPlayer();
        void pickItem();
        void update(SDL_Rect&);
        void fire();
        void isShooted(Bullet*);
        double getPlayerX();
        double getPlayerY();
};

class Player2 : public Player {
    public:
        Player2(std::string id = "");
        ~Player2();
        void handleKeyInput(SDL_Event&);
};

extern std::vector<Player*> players;

#endif
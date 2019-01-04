#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"

class Bullet;
class Item;

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
        bool _bombEquipped;
        double _hp; // HP
        double _defend; // defend coefficient
    public:
        friend class Bullet;
        friend class Item;
        friend class Obstacle;

        Item *helmet, *helmetUp, *gun, *bodyArmor, *bomb; // player equip
        Obj BloodStrip[2]; // background, white / red
        Player(std::string id = "");
        ~Player();
        void setInitialPosition(int, int);
        virtual void handleKeyInput(SDL_Event&);
        void move();
        void rotate();
        bool collideWall();
        bool collideOtherPlayer();
        bool collideObstacle();
        void pickItem();
        void fire();
        void isShooted(Bullet*);
        double getPlayerX();
        double getPlayerY();
        double getDeg();
        // change skin
        void changeSkin(PlayerType);
        // change helmet
        void changeHelmet(ItemType);
        // change bodyArmor
        void changeBodyArmor(ItemType);

        void update();

        void renderL(SDL_Rect&);
        void renderR(SDL_Rect&);
        PlayerState getState();
};

class Player2 : public Player {
    public:
        Player2(std::string id = "");
        ~Player2();
        void handleKeyInput(SDL_Event&);
};

extern std::vector<Player*> players;

#endif
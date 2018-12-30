#ifndef BULLET_H
#define BULLET_H

#include "Obj.h"

enum GunType {
    Gun, MachineGun
};

enum BulletState {
    flying, shooted
};

class Player; 

class Bullet: public Obj {
    private:
        std::string _fromID;
        std::string _type;
        double _bulletX, _bulletY; // center position
        double _dirX, _dirY;
        double _moveVel;
        double _deg;
        double _bulletSize;
        double _distance; // longest flying distance
        BulletState _state; // whether it shooted something
        void _move();
        void _collideWall();
        void _collideOtherPlayer();
        void _endDistance();
    public:
        Bullet() {};
        Bullet(Player&, GunType);
        ~Bullet(); 
        void update();
};

#endif
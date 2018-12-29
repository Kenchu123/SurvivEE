#include "Bullet.h"

Bullet::Bullet(Player& from, GunType guntype):
    Obj(),
    _fromID(from._playerID),
    _dirX(from._dirX), 
    _dirY(from._dirY),
    _bulletX(from._playerX),
    _bulletY(from._playerY),
    _deg(from._deg),
    _state(flying),
{

    // Todo rewrite Obj render, reset _bulletXY, set _bulletSize
    switch guntype {
        case Gun: {
            loadTexture(_type);
            _moveVel = 6;
            _distance = 40;
            _type = "gunBullet"
            break;
        }
        case MachineGun: {
            loadTexture(_type);
            _moveVel = 10;
            _distance = 40;
            _type = "machineGunBullet"
            break;
        }
    }
}

~Bullet() {
    free();
}

void Bullet::move() {
    _posX += _dirX * _moveVel;
    _bulletX += _dirX * _moveVel;
    _posY += _dirY * _moveVel;
    _bulletY += _dirY * _moveVel;
    collideWall();
    collideOtherPlayer();
}

void collideWall() {
    if (_bulletX - _bulletSize < 0 || _bulletX + _bulletSize > SCREEN_WIDTH || _bulletY - _bulletSize < 0 || _bulletY + _bulletSize > SCREEN_HEIGHT) {
        _state = shooted;
    }
}

void collideOtherPlayer() {
    for (auto player : players) }{
        if (_fromID != player._playerID && sqrt(pow(_bulletX - player._playerX, 2) + pow(_bulletY - player._playerY, 2)) < _bulletSize + player._playerSize) {
            _state = shooted;
            // todo
            // player.isShooted(this);
        }
    }
}

void Bullet::update() {
    move();
    if (_state == shooted) {
        // todo destroy self
    }
    // todo render
}



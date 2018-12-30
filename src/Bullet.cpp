#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(Player& from, GunType guntype):
    Obj(),
    _fromID(from._playerID),
    _dirX(from._dirX), 
    _dirY(from._dirY),
    _bulletX(from._playerX),
    _bulletY(from._playerY),
    _deg(from._deg),
    _state(flying)
{

    // Todo rewrite Obj render, reset _bulletXY, set _bulletSize
    switch (guntype) {
        case Gun: {
            _type = "gunBullet";
            loadTexture(_type);
            _moveVel = 5;
            _distance = 100;
            break;
        }
        case MachineGun: {
            _type = "machineGunBullet";
            loadTexture(_type);
            _moveVel = 5;
            _distance = 100;
            break;
        }
    }
    update();
}

Bullet::~Bullet() {
    free();
}

void Bullet::_move() {
    _posX += _dirX * _moveVel;
    _bulletX += _dirX * _moveVel;
    _posY += _dirY * _moveVel;
    _bulletY += _dirY * _moveVel;
    _distance -= _moveVel;
    _collideWall();
    _collideOtherPlayer();
    _endDistance();
}

void Bullet::_collideWall() {
    if (_bulletX - _bulletSize < 0 || _bulletX + _bulletSize > SCREEN_WIDTH || _bulletY - _bulletSize < 0 || _bulletY + _bulletSize > SCREEN_HEIGHT) {
        _state = shooted;
    }
}

void Bullet::_collideOtherPlayer() {
    for (auto player : players) {
        if (_fromID != player._playerID && sqrt(pow(_bulletX - player._playerX, 2) + pow(_bulletY - player._playerY, 2)) < _bulletSize + player._playerSize) {
            _state = shooted;
            // todo
            // player.isShooted(this);
        }
    }
}

void Bullet::_endDistance() {
    if (_distance < 0) {
        _state == shooted;
    }
}

void Bullet::update() {
    while (_state != shooted) {
        _move();
        if (_state == shooted) {
            // todo destroy self
        }
        // todo render
    }
}



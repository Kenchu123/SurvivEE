#include "Bullet.h"
#include "Player.h"

std::vector<Bullet*> bullets;

Bullet::Bullet(Player* from, GunType guntype):
    Obj(),
    _fromID(from->_playerID),
    _dirX(from->_dirX), 
    _dirY(from->_dirY),
    _bulletX(from->_playerX + from->_dirX * (from->getHeight() - from->_playerSize)),
    _bulletY(from->_playerY + from->_dirY * (from->getHeight() - from->_playerSize)),
    _deg(from->_deg),
    _state(flying)
{
    // Todo rewrite, reset _bulletXY, set _bulletSize
    // _posX = from->_playerX;
    // _posY = from->_playerY;
    switch (guntype) {
        case Gun: {
            _type = "GunBullet";
            loadTexture(_type);
            _moveVel = 10;
            _distance = 300;
            _bulletSize = _objHeight / 2;
            resize(10, 20); // resize the bullet w, h
            break;
        }
        case MachineGun: {
            _type = "MachineGunBullet";
            loadTexture(_type);
            _moveVel = 10;
            _distance = 300;
            _bulletSize = _objHeight / 2;
            resize(10, 20);
            break;
        }
        default:
            break;
    }
    std::cout << typeToString(guntype) << std::endl;
    // std::cout << "Bullet Position: " << _bulletX << " " << _bulletY << std::endl;
    // std::cout << "Bullet Direction: " << _dirX << " " << _dirY << std::endl;
    // std:: cout << "Bullet degree: " << _deg << std::endl;
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
        std::cout << "Bullet collide Wall\n";
    }
}

void Bullet::_collideOtherPlayer() {
    for (int i = 0;i < players.size(); i++) {
        if (_fromID != players[i]->_playerID && sqrt(pow(_bulletX - players[i]->_playerX, 2) + pow(_bulletY - players[i]->_playerY, 2)) < _bulletSize + players[i]->_playerSize) {
            _state = shooted;
            // todo
            std::cout << "Player is shooted\n";
            // player.isShooted(this);
        }
    }
}

void Bullet::_endDistance() {
    if (_distance < 0) {
        _state = shooted;
        std::cout << "Bullet out of distance\n";
        // std::cout << "Bullet Position: " << _bulletX << " " << _bulletY << std::endl;
    }
}

void Bullet::update() {
    // todo destroy self
    if (_state == shooted) {
        free();
        return;
    }
    _move();
    // todo render
    // std::cout << "Bullet _state: " << _state << std::endl;
    // std::cout << "Bullet Position: " << _posX << " " << _posY << std::endl;
    render(_bulletX, _bulletY, _deg);
}



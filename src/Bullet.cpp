#include "Bullet.h"
#include "Player.h"

std::vector<Bullet*> bullets;

Bullet::Bullet(Player* from, GunType guntype):
    Obj(),
    _fromID(from->_playerID),
    _dirX(from->_dirX), 
    _dirY(from->_dirY),
    _deg(from->_deg),
    _state(flying)
{
    switch (guntype) {
        case Gun: {
            _type = "GunBullet";
            loadTexture(_type);
            resize(10, 20); // resize the bullet w, h
            _moveVel = 10;
            _distance = 300;
            lethality = 50;
            break;
        }
        case MachineGun: {
            _type = "MachineGunBullet";
            loadTexture(_type);
            resize(10, 20); // resize the bullet w, h
            _moveVel = 10;
            _distance = 300;
            lethality = 50;
            break;
        }
        case ShotGun: {
            _type = "ShotGunBullet";
            loadTexture(_type);
            resize(30, 20); // resize the bullet w, h
            _moveVel = 10;
            _distance = 300;
            lethality = 50;
            break;
        }
        case SubMachineGun: {
            _type = "MachineGunBullet";
            loadTexture(_type);
            resize(10, 20); // resize the bullet w, h
            _moveVel = 10;
            _distance = 300;
            lethality = 50;
            break;
        }
        case AK47: {
            _type = "MachineGunBullet";
            loadTexture(_type);
            resize(10, 20); // resize the bullet w, h
            _moveVel = 10;
            _distance = 300;
            lethality = 50;
            break;
        }
        default:
            break;
    }
    _bulletSize = _objHeight / 2;
    _bulletX = from->_playerX + from->_dirX * (from->getHeight() - from->_playerSize + _objHeight);
    _bulletY = from->_playerY + from->_dirY * (from->getHeight() - from->_playerSize + _objHeight);
    _posX = _bulletX + 0.5 * _objWidth * _dirY;
    _posY = _bulletY - 0.5 * _objWidth * _dirX;
    // std::cout << _objWidth * 1 / 2 * _dirY << std::endl;
    // std::cout << _type << std::endl;
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
    if (_bulletX < 0 || _bulletX > LEVEL_WIDTH || _bulletY  < 0 || _bulletY > LEVEL_HEIGHT) {
        _state = shooted;
        // std::cout << "Bullet collide Wall\n";
    }
}

void Bullet::_collideOtherPlayer() {
    for (int i = 0;i < players.size(); i++) {
        if (_fromID != players[i]->_playerID && sqrt(pow(_bulletX - players[i]->_playerX, 2) + pow(_bulletY - players[i]->_playerY, 2)) < players[i]->_playerSize) {
            _state = shooted;
            players[i]->isShooted(this);
        }
    }
}

void Bullet::_endDistance() {
    if (_distance < 0) {
        _state = shooted;
        // std::cout << "Bullet out of distance\n";
    }
}

void Bullet::update() {
    if (_state == shooted) {
        // todo destroy self
        free();
        return;
    }
    _move();
    // set rotate point to make it's direction correct
    SDL_Point tmp;
    tmp.x = 0;
    tmp.y = 0;
}

void Bullet::renderL(SDL_Rect& camera) {
    if(_posX - camera.x < SCREEN_WIDTH / 2 && _posY - camera.y < SCREEN_HEIGHT) {
        SDL_Point tmp = {0, 0};
        render(_posX - camera.x, _posY - camera.y, _deg, &tmp);
    }
}
void Bullet::renderR(SDL_Rect& camera) {
    if(_posX - camera.x > 0) {
        SDL_Point tmp = {0, 0};
        render(_posX - camera.x + SCREEN_WIDTH / 2, _posY - camera.y, _deg, &tmp);
    }
}

// void Bullet::update2(SDL_Rect& camera) {
//     if (_state == shooted) {
//         // todo destroy self
//         free();
//         return;
//     }
//     _move();
//     // set rotate point to make it's direction correct

//     
// }



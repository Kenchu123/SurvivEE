#include "Player.h"

Player::Player(): Obj() {
    _dirX = 0; _dirY = -1;
    _rotVel = 0; _deg = 0;
    _moveVel = 4;
}
Player::~Player() {
    free();
    
}

void Player::setInitailPosition(int x, int y) {
    _posX = x;
    _posY = y;
    _playerSize = getWidth() / 2;
    _playerX = _posX + _playerSize;
    _playerY = _posY + getHeight() - _playerSize;
    _rotCenter.x = _playerSize; _rotCenter.y = getHeight() - _playerSize;;
    std::cout << "_playerSize: " << _playerSize << std::endl;
}

void Player::handleKeyInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: {
                _rotVel = -5;
                break;
            }
            case SDLK_RIGHT: {
                _rotVel = +5;
                break;
            }
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: _rotVel = 0; break;
            case SDLK_RIGHT: _rotVel = 0; break;
        }
    }
}

void Player::move() {
    _posX += _dirX * _moveVel;
    _playerX += _dirX * _moveVel;
    // check collide with wall left and right
    if (_playerX - _playerSize < 0 || _playerX + _playerSize > SCREEN_WIDTH) {
        _playerX -= _dirX * _moveVel;
        _posX -= _dirX * _moveVel;
    }

    _posY += _dirY * _moveVel;
    _playerY += _dirY * _moveVel;
    // check collide with wall up and down
    if (_playerY - _playerSize < 0 || _playerY + _playerSize > SCREEN_HEIGHT) {
        _posY -= _dirY * _moveVel;
        _playerY -= _dirY * _moveVel;
    }
}
void Player::rotate() {
    _deg += _rotVel;
    _dirX = sin(_deg * PI / 180);
    _dirY = -cos(_deg * PI / 180);
}
void Player::collideWall() {

}
void Player::collideItem() {

}
void Player::collideOhterPlayer() {

}
void Player::update() {
    rotate();
    move();
    // std::cout << "Player _posX, _posY: " << _posX << " " << _posY << std::endl;
    // std::cout << "Player _dirX, _dirY: " << _dirX << " " << _dirY << std::endl;
    // std::cout << "Player _playerX, _playerY: " << _playerX << " " << _playerY << std::endl;
    render(_posX, _posY, _deg, &_rotCenter);
}
void Player::renderPlayer() {

}
#include "Player.h"

Player::Player(): Obj() {
    _velX = 0;
    _velY = -10;
    _rotVel = 0;
    _moveVel = 0;
    _deg = 0;
}
Player::~Player() {
    free();
}

void Player::setInitailPosition(int x, int y) {
    _posX = x;
    _posY = y;
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
            case SDLK_UP: {
                _moveVel = -1;
                break;
            }
            case SDLK_DOWN: {
                _moveVel = 1;
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
            case SDLK_UP: _moveVel = 0; break;
            case SDLK_DOWN: _moveVel = 0; break;
        }
    }
}

void Player::move() {
    _posX += _velX * _moveVel;
    _posY += _velY * _moveVel;
}
void Player::rotate() {
    _deg += _rotVel;
    double tmpX = -_velX, tmpY = -_velY;
    _velX = -sin(_deg * PI / 180) * 10;
    _velY = cos(_deg * PI / 180) * 10;
}
void Player::collideWall() {

}
void Player::collideItem() {

};
void Player::collideOhterPlayer() {

}
void Player::update() {
    move();
    rotate();
    SDL_Point p;
    p.x = _posX;
    p.y = _posY;
    render(_posX, _posY, _deg, NULL);
}
void Player::renderPlayer() {

}
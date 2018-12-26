#include "Player.h"

Player::Player(): Obj() {
    _dirX = 0;
    _dirY = -1;
    _rotVel = 0;
    _moveVel = -4;
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
    _posY += _dirY * _moveVel;
}
void Player::rotate() {
    _deg += _rotVel;
    // double _v = sqrt(pow(_dirX, 2) + pow(_dirY, 2));
    _dirX = -sin(_deg * PI / 180);
    _dirY = cos(_deg * PI / 180);
}
void Player::collideWall() {

}
void Player::collideItem() {

};
void Player::collideOhterPlayer() {

}
void Player::update() {
    rotate();
    move();
    SDL_Point p;
    p.x = getWidth() / 2;
    p.y = getHeight() - getWidth() / 2;
    render(_posX, _posY, _deg, &p);
}
void Player::renderPlayer() {

}
#include "Player.h"

Player::Player(): Obj() {
    _velX = 0;
    _velY = 0;
    _moveVel = 10;
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
            case SDLK_LEFT: _velX -= _moveVel; break;
            case SDLK_RIGHT: _velX += _moveVel; break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: _velX += _moveVel; break;
            case SDLK_RIGHT: _velX -= _moveVel; break;
        }
    }
}

void Player::move() {
    _posX += _velX;
    _posY += _velY;
}
void Player::rotate() {

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
    render(_posX, _posY);
}
void Player::renderPlayer() {

}
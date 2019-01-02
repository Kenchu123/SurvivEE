#include "Player.h"
#include "Bullet.h"
#include "Utility.h"
#include "Item.h"

std::vector<Player*> players;

Player::Player(std::string id): 
    Obj(), 
    _playerID(id),
    _dirX(0), _dirY(-1),
    _rotVel(0), _deg(0), 
    _moveVel(0), 
    _playerType(GunPlayer),
    _state(alive),
    _hp(500)
{
    loadTexture(typeToString(_playerType));
    std::cout << typeToString(_playerType) << std::endl; 
    std::cout << "Player Created : " << _playerID << " " << typeToString(_playerType) << std::endl;
}
Player::~Player() {
    free();   
}

// set player initial postion
void Player::setInitialPosition(int x, int y) {
    _posX = x;
    _posY = y;
    _playerSize = getWidth() / 2;
    _playerX = _posX + _playerSize;
    _playerY = _posY + getHeight() - _playerSize;
    _rotCenter.x = _playerSize; _rotCenter.y = getHeight() - _playerSize;;
}

// player handle key input
void Player::handleKeyInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:{
                _moveVel = 4;
                loadedSound.playSound("footstep4"); 
                break;
            }
            case SDLK_DOWN:{
                _moveVel = -4;
                loadedSound.playSound("footstep4"); 
                break;
            }
            case SDLK_LEFT: _rotVel = -5; break;
            case SDLK_RIGHT: _rotVel = +5; break;
            case SDLK_z: fire(); break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP: _moveVel = 0; break;
            case SDLK_DOWN: _moveVel = 0; break;
            case SDLK_LEFT: _rotVel = 0; break;
            case SDLK_RIGHT: _rotVel = 0; break;
        }
    }
}

// player move
void Player::move() {
    _posX += _dirX * _moveVel;
    _playerX += _dirX * _moveVel;
    // check collide with wall left and right

    if (collideWall() || collideOtherPlayer()) {
        _playerX -= _dirX * _moveVel;
        _posX -= _dirX * _moveVel;
    }

    _posY += _dirY * _moveVel;
    _playerY += _dirY * _moveVel;

    // check collide with wall up and down
    if (collideWall() || collideOtherPlayer()) {
        _posY -= _dirY * _moveVel;
        _playerY -= _dirY * _moveVel;
    }
}

// set player rotate
void Player::rotate() {
    _deg += _rotVel;
    _dirX = sin(_deg * PI / 180);
    _dirY = -cos(_deg * PI / 180);
}

// check player collide with wall
bool Player::collideWall() {
    return _playerX - _playerSize < 0 || _playerX + _playerSize > LEVEL_WIDTH || _playerY - _playerSize < 0 || _playerY + _playerSize > LEVEL_HEIGHT;
}

void Player::pickItem() {
    for (int i = 0; i < items.size(); i++) {
        if (sqrt(pow(_playerX - items[i]->getItemX(), 2) + pow(_playerY - items[i]->getItemY(), 2)) < _playerSize + items[i]->getWidth() / 2) {
            items[i]->isPicked(this);
            // todo player affect
            // todo remove item from items
        }
    }
}

// check player collide with other player
bool Player::collideOtherPlayer() {
    for (int i = 0;i < players.size(); i++) {
        if (_playerID != players[i]->_playerID && sqrt(pow(_playerX - players[i]->_playerX, 2) + pow(_playerY - players[i]->_playerY, 2)) < _playerSize + players[i]->_playerSize) return 1;
    }
    return 0;
}

void Player::fire() {
    std::cout << "Fire called" << std::endl;
    Bullet* bullet = new Bullet(this, (GunType)_playerType);
    switch (_playerType) {
        case DefaultPlayer: break;
        case GunPlayer: {
            loadedSound.playSound("DefaultGunShot");
            break;
        }
        case MachineGunPlayer: {
            loadedSound.playSound("MachineGunShot");
            break;
        }
        case ShotGunPlayer: {
            loadedSound.playSound("ShotGunShot");
            break;
        }
        case SubMachineGunPlayer: {
            loadedSound.playSound("MachineGunShot");
            break;
        }
        case AK47Player: {
            loadedSound.playSound("MachineGunShot");
            break;
        }
    }
    // bullets.emplace_back(this, (GunType)_playerType);
    bullets.push_back(bullet);
}

void Player::isShooted(Bullet* bullet) {
    _hp -= bullet->lethality;
    // todo hurt animation
    std::cout << "Player " << _playerID << " is shooted " << _hp << std::endl;
    if (_hp < 0) {
        // todo death
        _state = dead;
    }
}

// run rotate, move render 
// todo collectItem
// todo set State
void Player::update(SDL_Rect& camera) {
    if (_state == dead) {
        // todo destroy self
        free();
        return;
    }
    move();
    rotate();
    pickItem();
    render(_posX - camera.x, _posY - camera.y, _deg, &_rotCenter);
    // std::cout << "Player " << _playerID << ": posX, posY" << _posX << " " << _posY << std::endl;
}

double Player::getPlayerX() {return _playerX;};
double Player::getPlayerY() {return _playerY;};
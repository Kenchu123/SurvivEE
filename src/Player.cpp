#include "Player.h"
#include "Bullet.h"
#include "Utility.h"
#include "Obstacle.h"
#include "Item.h"
#include "Timer.h"

std::vector<Player*> players;

Player::Player(std::string id): 
    Obj(), 
    _playerID(id),
    _dirX(0), _dirY(-1),
    _rotVel(0), _deg(0), 
    _moveVel(0), 
    _playerType(GunPlayer),
    _state(alive),
    _bombEquipped(false),
    _hp(500),
    _defend(1),
    helmet(NULL),
    gun(NULL),
    bomb(NULL)
{
    loadTexture(typeToString(_playerType));
    std::cout << typeToString(_playerType) << std::endl; 
    std::cout << "Player Created : " << _playerID << " " << typeToString(_playerType) << std::endl;
    BloodStrip[0].loadTexture("BloodStripBackground");
    // BloodStrip[1].loadTexture("BloodStripRed");
}
Player::~Player() {
    free();   
    for (int i = 0;i < 2; i++) BloodStrip[i].free();
    helmet->free(), gun->free(), bomb->free();
    helmet = NULL, gun = NULL, bomb = NULL;
}

// set player initial postion
void Player::setInitialPosition(int x, int y) {
    _posX = x;
    _posY = y;
    _playerSize = getWidth() / 2;
    _playerX = _posX + _playerSize;
    _playerY = _posY + getHeight() - _playerSize;
    _rotCenter.x = _playerSize; _rotCenter.y = getHeight() - _playerSize;
}

// player handle key input
void Player::handleKeyInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:{
                _moveVel = 4;
                loadedSound.playSound(1, "footstep", -1); 
                break;
            }
            case SDLK_DOWN:{
                _moveVel = -4;
                loadedSound.playSound(1, "footstep", -1); 
                break;
            }
            case SDLK_LEFT: _rotVel = -5; break;
            case SDLK_RIGHT: _rotVel = +5; break;
            case SDLK_RETURN: fire(); break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP: _moveVel = 0;Mix_Pause(1); break;
            case SDLK_DOWN: _moveVel = 0;Mix_Pause(1); break;
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

    if (collideWall() || collideOtherPlayer() || collideObstacle()) {
        _playerX -= _dirX * _moveVel;
        _posX -= _dirX * _moveVel;
    }

    _posY += _dirY * _moveVel;
    _playerY += _dirY * _moveVel;

    // check collide with wall up and down
    if (collideWall() || collideOtherPlayer() || collideObstacle()) {
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

bool Player::collideObstacle() {
    for(int i = 0; i < obstacles.size(); i++) {
        if(sqrt(pow(_playerX - obstacles[i]->_obstacleX, 2) + pow(_playerY - obstacles[i]->_obstacleY, 2)) < _playerSize + obstacles[i]->getWidth() / 2) return 1;
    }
    return 0;
}


void Player::fire() {
    if(!_bombEquipped) {
        std::cout << "Fire called" << std::endl;
        Bullet* bullet = new Bullet(this, (ItemType)_playerType);
        switch(_playerType) {
            case GunPlayer: {
                loadedSound.playSound(0, "DefaultGunShot", 0);
                break;
            }
            case MachineGunPlayer: {
                loadedSound.playSound(0, "MachineGunShot", 0);
                break;
            }
            case ShotGunPlayer: {
                loadedSound.playSound(0, "ShotGunShot", 0);
                break;
            }
            case FireGunPlayer: {
                loadedSound.playSound(0, "ShotGunShot", 0);
                break;
            }
            case AK47Player: {
                loadedSound.playSound(0, "MachineGunShot", 0);
                break;
            }
            default: break;
        }
        // bullets.emplace_back(this, (GunType)_playerType);
        bullets.push_back(bullet);
    }
    else {
        std::cout << "Bomb called" << std::endl;
        Bullet* bullet = new Bullet(this, Bomb);
        bullets.push_back(bullet);
    }
}

void Player::isShooted(Bullet* bullet) {
    _hp -= bullet->lethality * _defend;
    // todo hurt animation
    std::cout << "Player " << _playerID << " is shooted " << _hp << std::endl;
    if (_hp <= 0) {
        // todo death
        _state = dead;
    }
}

void Player::changeSkin(PlayerType newPlayerType) {
    loadTexture(typeToString(newPlayerType));
    _playerType = newPlayerType;
    _playerSize = getWidth() / 2;
    _rotCenter.x = _playerSize; _rotCenter.y = getHeight() - _playerSize;

}

// run rotate, move render 
// todo collectItem
// todo set State
void Player::update() {
    if (_state == dead) {
        // todo destroy self
        BloodStrip[1].resize(BloodStrip[0].getWidth() * (_hp / 500), BloodStrip[0].getHeight());
        free();
        return;
    }
    // update blood
    if(_hp > 100){
        BloodStrip[1].loadTexture("BloodStripWhite");
        BloodStrip[1].resize(BloodStrip[0].getWidth() * (_hp / 500), BloodStrip[0].getHeight());
    }
    else {
        BloodStrip[1].loadTexture("BloodStripRed");
        BloodStrip[1].resize(BloodStrip[0].getWidth() * (_hp / 500), BloodStrip[0].getHeight());
    }
    move();
    rotate();
    pickItem();
    // std::cout << "Player " << _playerID << ": posX, posY" << _posX << " " << _posY << std::endl;
}

void Player::renderL(SDL_Rect& camera) {
    if (_state == dead) return;
    if(_posX - camera.x < SCREEN_WIDTH / 2 && _posY - camera.y < SCREEN_HEIGHT) {
        render(_posX - camera.x, _posY - camera.y, _deg, &_rotCenter);
        if (helmet != NULL) {
            helmet->SetPosition(_playerX, _playerY);
            helmet->SetAngle(_deg);
            helmet->renderL(camera);
        }
    }
}

void Player::renderR(SDL_Rect& camera) {
    if (_state == dead) return;
    if(_posX - camera.x > 0) {
        render(_posX - camera.x + SCREEN_WIDTH / 2, _posY - camera.y, _deg, &_rotCenter);
        if (helmet != NULL) {
            helmet->SetPosition(_playerX, _playerY);
            helmet->SetAngle(_deg);
            helmet->renderR(camera);
        }
    }
}

double Player::getPlayerX() { return _playerX; }
double Player::getPlayerY() { return _playerY; }
double Player::getDeg() { return _deg; }

Player2::Player2(std::string id): Player(id) {}

Player2::~Player2() {
    free();   
}

void Player2::handleKeyInput(SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_r:{
                _moveVel = 4;
                loadedSound.playSound(2, "footstep", -1); 
                break;
            }
            case SDLK_f:{
                _moveVel = -4;
                loadedSound.playSound(2, "footstep", -1); 
                break;
            }
            case SDLK_d: _rotVel = -5; break;
            case SDLK_g: _rotVel = +5; break;
            case SDLK_z: fire(); break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_r: _moveVel = 0; Mix_Pause(2); break;
            case SDLK_f: _moveVel = 0; Mix_Pause(2); break;
            case SDLK_d: _rotVel = 0; break;
            case SDLK_g: _rotVel = 0; break;
        }
    }
}



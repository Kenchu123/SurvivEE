#include "Item.h"
#include "Utility.h"

std::vector<Item*> items;

Item::Item(): Obj(), _type(""), _itemX(0), _itemY(0), _deg(0), _state(unPicked) {}

Item::Item(std::string s, double x, double y):
    Obj(), _type(s), _itemX(x), _itemY(y), _deg(0), _state(unPicked)
{
    loadTexture(_type);
    resize(80, 80);
    _posX = _itemX - getWidth() * 0.5;
    _posY = _itemY - getHeight() * 0.5;
    std::cout << _type << " " << std::endl;
}

Item::~Item() {
    free();
}

void Item::free() {
    _objTexture = NULL;
    _type = "";
    _objHeight = 0, _objWidth = 0;
    _itemX = 0, _itemY = 0;
    _state = Picked;
}

void Item::SetPosition(double x, double y) {
    _itemX = x, _itemY = y;
    _posX = _itemX - getWidth() * 0.5;
    _posY = _itemY - getHeight() * 0.5;
}

void Item::update() {
    if (_state == unPicked) {
        //
    }
    return;
}

void Item::renderL(SDL_Rect& camera) {
    if(_posX - camera.x < SCREEN_WIDTH / 2 && _posY - camera.y < SCREEN_HEIGHT) {
        render(_posX - camera.x, _posY - camera.y, _deg);
    }
}
void Item::renderR(SDL_Rect& camera) {
    if(_posX - camera.x > 0) {
        render(_posX - camera.x + SCREEN_WIDTH / 2, _posY - camera.y, _deg);
    }  
}

void Item::isPicked(Player* player) {
    _state = Picked;
    if(_type == "Gun") {
        player->_playerType = GunPlayer;
    }
    else if(_type == "MachineGun") {
        player->_playerType = MachineGunPlayer;
    }
    else if(_type == "ShotGun") {
        player->_playerType = ShotGunPlayer;
    }
    else if(_type == "SubMachineGun") {
        player->_playerType = MachineGunPlayer;
    }
    else if(_type == "AK47") {
        player->_playerType = MachineGunPlayer;   
    }
    else if(_type == "Helmet1") {
        switch(player -> _playerType) {
            case GunPlayer : {
                player -> _playerType = GunPlayerHelmet1;
                break;
            }
            case GunPlayerHelmet2 : {
                player -> _playerType = GunPlayerHelmet1;
                break;
            }
            case MachineGunPlayer : {
                player -> _playerType = MachineGunPlayerHelmet1;
                break;
            }
            case MachineGunPlayerHelmet2 : {
                player -> _playerType = MachineGunPlayerHelmet1;
                break;
            }
            case ShotGunPlayer : {
                player -> _playerType = ShotGunPlayerHelmet1;
                break;
            }
            case ShotGunPlayerHelmet2 : {
                player -> _playerType = ShotGunPlayerHelmet1;
                break;
            }
        }
    }
    else if(_type == "Helmet2") {
        switch(player -> _playerType) {
            case GunPlayer : {
                player -> _playerType = GunPlayerHelmet2;
                break;
            }
            case GunPlayerHelmet1 : {
                player -> _playerType = GunPlayerHelmet2;
                break;
            }
            case MachineGunPlayer : {
                player -> _playerType = MachineGunPlayerHelmet2;
                break;
            }
            case MachineGunPlayerHelmet1 : {
                player -> _playerType = MachineGunPlayerHelmet2;
                break;
            }
            case ShotGunPlayer : {
                player -> _playerType = ShotGunPlayerHelmet2;
                break;
            }
            case ShotGunPlayerHelmet1 : {
                player -> _playerType = ShotGunPlayerHelmet2;
                break;
            }
        }
    }
    player->loadTexture(typeToString(player->_playerType));
    player->_playerSize = getWidth() / 2;
    player->_rotCenter.x = player->_playerSize; player->_rotCenter.y = player->getHeight() - player->_playerSize;
    free();
}
#include "Item.h"
#include "Utility.h"

std::vector<Item*> items;

Item::Item(): Obj(), _type(Default), _itemX(0), _itemY(0), _deg(0), _state(unPicked) {}

Item::Item(ItemType type, double x, double y):
    Obj(), _type(type), _itemX(x), _itemY(y), _deg(0), _state(unPicked)
{
    loadTexture(typeToString(type));
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
    _type = Default;
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
    switch(_type) {
        case Gun: player->_playerType = GunPlayer; break;
        case MachineGun: player->_playerType = MachineGunPlayer; break;
        case ShotGun: player->_playerType = ShotGunPlayer; break;
        case SubMachineGun: player->_playerType = MachineGunPlayer; break;
        case AK47: player->_playerType = MachineGunPlayer; break;
        case Bandage: {
            if(player->_hp + 200 >= 500) player->_hp = 500;
            else player->_hp += 200; 
            break;
        }
        case LifeBox: player->_hp = 500; break;
        default: break;
    }

    player->loadTexture(typeToString(player->_playerType));
    player->_playerSize = getWidth() / 2;
    player->_rotCenter.x = player->_playerSize; player->_rotCenter.y = player->getHeight() - player->_playerSize;
    free();
}
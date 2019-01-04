#include "Item.h"
#include "Player.h"
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

void Item::SetAngle(double angle) {
    _deg = angle;
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
        case Gun: player->changeSkin(GunPlayer); break;
        case MachineGun: player->changeSkin(MachineGunPlayer); break;
        case ShotGun: player->changeSkin(ShotGunPlayer); break;
        case FireGun: player->changeSkin(FireGunPlayer); break;
        case AK47: player->changeSkin(AK47Player); break;
        case Bomb: player->_bombEquipped = true; break;
        case BodyArmor1: player->_defend *= 0.9; player->changeBodyArmor(BodyArmor1); break;
        case BodyArmor2: player->_defend *= 0.8; player->changeBodyArmor(BodyArmor2); break;
        case Helmet1: player->_defend *= 0.9; player->changeHelmet(Helmet1); break;
        case Helmet2: player->_defend *= 0.8; player->changeHelmet(Helmet2); break;
        case Bandage: player->_hp = player->_hp + 200 > 500 ? 500 : player->_hp + 200; break;
        case LifeBox: player->_hp = 500; break;
        default: break;
    }
    // player->loadTexture(typeToString(player->_playerType));
    // player->_playerSize = getWidth() / 2;
    // player->_rotCenter.x = player->_playerSize; player->_rotCenter.y = player->getHeight() - player->_playerSize;
    free();
}
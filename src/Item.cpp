#include "Item.h"
#include "Utility.h"

std::vector<Item*> items;

Item::Item(): Obj(), _type(""), _itemX(0), _itemY(0), _state(unPicked) {}

Item::Item(std::string s, double x, double y):
    Obj(), _type(s), _itemX(x), _itemY(y), _state(unPicked)
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

void Item::SetPosition(double& x, double& y) {
    _itemX = x, _itemY = y;
    _posX = _itemX - getWidth() * 0.5;
    _posY = _itemY - getHeight() * 0.5;
}

void Item::update(SDL_Rect& camera) {
    if (_state == unPicked) render(_posX - camera.x, _posY- camera.y);
    return;
}

void Item::isPicked(Player* player) {
    _state = Picked;
    if(_type == "Gun") {
        player->_playerType = GunPlayer;
        player->loadTexture(typeToString(player->_playerType));
        free();
    }
    else if(_type == "MachineGun") {
        player->_playerType = MachineGunPlayer;
        player->loadTexture(typeToString(player->_playerType));
        free();
    }
    else if(_type == "ShotGun") {
        player->_playerType = ShotGunPlayer;
        player->loadTexture(typeToString(player->_playerType));
        free();
    }
    else if(_type == "SubMachineGun") {
        player->_playerType = MachineGunPlayer;
        player->loadTexture(typeToString(player->_playerType));
        free();
    }
    else if(_type == "AK47") {
        player->_playerType = MachineGunPlayer;
        player->loadTexture(typeToString(player->_playerType));
        free();
    }
}
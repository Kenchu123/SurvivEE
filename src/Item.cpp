#include "Item.h"

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
    _type = "";
    _itemX = 0, _itemY = 0;
    _state = unPicked;
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

Item* Item::isPicked() {
    _state = Picked;
    return this;
}
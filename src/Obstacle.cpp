#include "Obstacle.h"
#include "Player.h"
#include "Utility.h"

std::vector<Obstacle*> obstacles;

Obstacle::Obstacle(std::string s, double x, double y):
    Obj(), 
    _type(s),
    _obstacleX(x),
    _obstacleY(y),
    _obstacleRadius(0)
{
    loadTexture(_type);
    _posX = _obstacleX - getWidth() * 0.5;
    _posY = _obstacleY - getHeight() * 0.5;
    resize(100, 100);
    std::cout << _type << std::endl;
}

Obstacle::~Obstacle() {
    free();
}

void Obstacle::update(SDL_Rect& camera) {
    render(_posX - camera.x, _posY- camera.y);
    return;
}




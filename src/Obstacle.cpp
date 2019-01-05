#include "Obstacle.h"
#include "Player.h"
#include "Utility.h"

std::vector<Obstacle*> obstacles;

Obstacle::Obstacle(ObstacleType type, double x, double y, double deg):
    Obj(), 
    _type(type),
    _obstacleX(x),
    _obstacleY(y),
    _obstacleRadius(0),
    _deg(deg)
{
    loadTexture(typeToString(_type));
    resize(100, 100);
    _posX = _obstacleX - getWidth() * 0.5;
    _posY = _obstacleY - getHeight() * 0.5;
    std::cout << _type << std::endl;
}

Obstacle::~Obstacle() {
    free();
}

void Obstacle::update() {
    //
    return;
}

void Obstacle::renderL(SDL_Rect& camera) {
    if(_posX - camera.x < SCREEN_WIDTH / 2 && _posY - camera.y < SCREEN_HEIGHT) {
        render(_posX - camera.x, _posY - camera.y, _deg);
    }
}
void Obstacle::renderR(SDL_Rect& camera) {
    if(_posX - camera.x > 0) {
        render(_posX - camera.x + SCREEN_WIDTH / 2, _posY - camera.y, _deg);
    }
}




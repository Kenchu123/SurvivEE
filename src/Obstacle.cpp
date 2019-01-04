#include "rObstacle.h"
#include "Player.h"
#include "Utility.h"

std::vector<rObstacle*> robstacles;

rObstacle::rObstacle(std::string s, double x, double y):
    Obj(), 
    _type(s),
    _obstacleX(x),
    _obstacleY(y),
    _obstacleRadius(0)
{
    loadTexture(_type);
    resize(100, 100);
    _posX = _obstacleX - getWidth() * 0.5;
    _posY = _obstacleY - getHeight() * 0.5;
    std::cout << _type << std::endl;
}

rObstacle::~rObstacle() {
    free();
}

void rObstacle::update() {
    //
    return;
}

void rObstacle::renderL(SDL_Rect& camera) {
    if(_posX - camera.x < SCREEN_WIDTH / 2 && _posY - camera.y < SCREEN_HEIGHT) {
        render(_posX - camera.x, _posY - camera.y);
    }
}
void rObstacle::renderR(SDL_Rect& camera) {
    if(_posX - camera.x > 0) {
        render(_posX - camera.x + SCREEN_WIDTH / 2, _posY - camera.y);
    }
}




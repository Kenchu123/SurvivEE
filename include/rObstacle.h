#ifndef ROBSTACLE_H
#define ROBSTACLE_H

#include "Obj.h"

class rObstacle : public Obj {
    protected:
        std::string _type;
        rObstacleType _obstacleType;
        double _obstacleX, _obstacleY;
        double _obstacleRadius;
    public:
    friend class Player;
    friend class Bullet;
    rObstacle(std::string, double, double);
    ~rObstacle();
    void update();
    void renderL(SDL_Rect&);
    void renderR(SDL_Rect&);
};

extern std::vector<rObstacle*> robstacles;

#endif
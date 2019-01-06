#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Obj.h"

class Obstacle : public Obj {
    protected:
        // ObstacleType _obstacleType;
        double _obstacleX, _obstacleY;
        double _obstacleRadius;
        double _deg;
    public:
    ObstacleType _type;
    friend class Player;
    friend class Bullet;
    Obstacle(ObstacleType, double, double, double deg = 0);
    ~Obstacle();
    void update();
    void renderL(SDL_Rect&);
    void renderR(SDL_Rect&);
    void resize(int, int);
    double getObsX() { return _obstacleX; }
    double getObsY() { return _obstacleY; }
};

extern std::vector<Obstacle*> obstacles;

#endif
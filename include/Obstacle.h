#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Obj.h"

class Obstacle : public Obj {
    protected:
        std::string _type;
        ObstacleType _obstacleType;
        double _obstacleX, _obstacleY;
        double _obstacleRadius;
    public:
    friend class Player;
    Obstacle(std::string, double, double);
    ~Obstacle();
    void update(SDL_Rect& camera);
};

extern std::vector<Obstacle*> obstacles;

#endif
#ifndef FOOD_H
#define FOOD_H

#include "gameobject.h"

class Food : public GameObject
{
public:
    Food();
    int getGridX();
    int getGridY();

    void setGridPos(int x, int y);

private:
    int gridX, gridY;
};

#endif // FOOD_H

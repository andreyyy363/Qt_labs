#ifndef ENEMY_H
#define ENEMY_H

#include "food.h"
#include "gameobject.h"
#include <QRandomGenerator>

class Enemy : public GameObject {
public:
    Enemy(int gridSize, int cellSize);
    int getGridX();
    int getGridY();

    void moveRandomly(QVector<Food*> &foods, QVector<Enemy*> &enemies);
    void setGridPos(int x, int y);

private:
    int gridX;
    int gridY;
    int gridSize;
    int cellSize;

    bool isEnemyAt(int x, int y, const QVector<Enemy*>& enemies);
    bool isFoodAt(int x, int y, const QVector<Food*>& foods);

};

#endif // ENEMY_H

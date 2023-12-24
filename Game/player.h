#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class Player : public GameObject {
public:
    Player(int grSize, int cSize);

    int getEnergy() const;
    int getGridX();
    int getGridY();


    void move(int direction);
    void energyDecrement();

    void setGridPos(int x, int y);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setCanMove(bool canMove);

    bool getCanMove() const;

private:
    int energy;
    int points;
    int gridX;
    int gridY;
    int gridSize;
    int cellSize;

    bool isDragging;
    bool canMove;

    QPointF offset;
    QPointF initialPos;
};

#endif // PLAYER_H

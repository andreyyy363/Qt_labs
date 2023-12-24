#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGraphicsScene>
#include "gameobject.h"
#include "player.h"

class GameField : public QGraphicsScene
{
public:
    GameField(int size, int cellSize);
    Player *player;

    void addObjectToGrid(GameObject *object, int gridX, int gridY);
    void keyPressEvent(QKeyEvent *event) override;

private:
    int size;
    int cellSize;
    void initializeGrid();
};

#endif // GAMEFIELD_H

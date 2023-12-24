#include "gamefield.h"
#include <QGraphicsRectItem>
#include <QBrush>

GameField::GameField(int size, int cellSize)
    : size(size), cellSize(cellSize)
{
    initializeGrid();
}

// Create a grid of cells
void GameField::initializeGrid()
{

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            QGraphicsRectItem *cell = new QGraphicsRectItem(i * cellSize, j * cellSize, cellSize, cellSize);
            cell->setBrush(QBrush(Qt::white));
            addItem(cell);
        }
}

// Place an object on the grid
void GameField::addObjectToGrid(GameObject *object, int gridX, int gridY)
{

    qreal x = gridX * cellSize + 0.5 * (cellSize - object->boundingRect().width());
    qreal y = gridY * cellSize + 0.5 * (cellSize - object->boundingRect().height());
    object->setPosition(QPointF(x, y));
    addItem(object);
}

void GameField::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
}

#include "food.h"

Food::Food()
    : GameObject(QPainterPath(), Qt::green)
{
    // Initialization of the shape and color for the food (green apple)
    QPainterPath stem;
    stem.moveTo(10, 0);
    stem.lineTo(10, 5);

    QPainterPath body;
    body.addEllipse(0, 5, 20, 20);

    QPainterPath leaf;
    leaf.moveTo(15, 5);
    leaf.quadTo(25, 0, 15, 10);

    shape = stem + body + leaf;
    setPath(shape);
}

// Set the object position on the grid
void Food::setGridPos(int x, int y)
{
    gridX = x;
    gridY = y;
}

int Food::getGridX()
{
    return gridX;
}

int Food::getGridY()
{
    return gridY;
}

#include "enemy.h"

Enemy::Enemy(int gridSize, int cellSize)
    : GameObject(QPainterPath(), Qt::red),
    gridX(0), gridY(0), gridSize(gridSize), cellSize(cellSize)
{
    // Draw the main square
    shape.addRect(0, 0, cellSize, cellSize);

    // Draw the eyes
    shape.addEllipse(cellSize * 0.25, cellSize * 0.25, cellSize * 0.2, cellSize * 0.2);
    shape.addEllipse(cellSize * 0.55, cellSize * 0.25, cellSize * 0.2, cellSize * 0.2);

    // Draw the mouth
    shape.moveTo(cellSize * 0.2, cellSize * 0.7);
    shape.arcTo(cellSize * 0.2, cellSize * 0.5, cellSize * 0.6, cellSize * 0.4, 180, -180);

    setPath(shape);
    setTransformOriginPoint(boundingRect().center());
}

void Enemy::moveRandomly(QVector<Food*> &foods, QVector<Enemy*> &enemies)
{
    int direction;
    int newX, newY;

    // Generate random direction for enemy
    do {
        direction = QRandomGenerator::global()->bounded(8);

        switch (direction)
        {
        case 0:  // Up
            newX = gridX;
            newY = qMax(0, gridY - 1);
            break;
        case 1:  // Left
            newX = qMax(0, gridX - 1);
            newY = gridY;
            break;
        case 2:  // Down
            newX = gridX;
            newY = qMin(gridY + 1, gridSize - 1);
            break;
        case 3:  // Right
            newX = qMin(gridX + 1, gridSize - 1);
            newY = gridY;
            break;
        case 4:  // Up and left
            newX = qMax(0, gridX - 1);
            newY = qMax(0, gridY - 1);
            break;
        case 5:  // Up and right
            newX = qMin(gridX + 1, gridSize - 1);
            newY = qMax(0, gridY - 1);
            break;
        case 6:  // Down and left
            newX = qMax(0, gridX - 1);
            newY = qMin(gridY + 1, gridSize - 1);
            break;
        case 7:  // Down and right
            newX = qMin(gridX + 1, gridSize - 1);
            newY = qMin(gridY + 1, gridSize - 1);
            break;
        }

        // Check if the cell is occupied
    } while (isFoodAt(newX, newY, foods) || isEnemyAt(newX, newY, enemies));

    // Set new coordinates on the grid
    gridX = newX;
    gridY = newY;

    qreal x = gridX * cellSize + 0.5 * (cellSize - boundingRect().width());
    qreal y = gridY * cellSize + 0.5 * (cellSize - boundingRect().height());
    setPos(x, y);
}

bool Enemy::isEnemyAt(int x, int y, const QVector<Enemy*>& enemies)
{
    // Check if there is an enemy in cell (x, y)
    for (Enemy *enemy : enemies)
        if (enemy != this && enemy->getGridX() == x && enemy->getGridY() == y)
            return true;

    return false;
}

bool Enemy::isFoodAt(int x, int y, const QVector<Food*>& foods)
{
    // Check if there is food in cell (x, y)
    for (Food *food : foods)
        if (food->getGridX() == x && food->getGridY() == y)
            return true;

    return false;
}

// Set the object position on the grid
void Enemy::setGridPos(int x, int y)
{
    gridX = x;
    gridY = y;
}

int Enemy::getGridX()
{
    return gridX;
}

int Enemy::getGridY()
{
    return gridY;
}

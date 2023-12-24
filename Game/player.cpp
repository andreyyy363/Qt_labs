#include "player.h"
#include <QCursor>

Player::Player(int grSize, int cSize)
    : GameObject(QPainterPath(), Qt::blue), energy(3), points(0), isDragging(false), gridX(0), gridY(0)
{

    gridSize = grSize;
    cellSize = cSize;

    // Calculate the center of the player
    QPointF center = QPointF(cellSize / 2, cellSize / 2);

    // Draw the main square
    shape.addRect(0, 0, cellSize, cellSize);

    // Draw the eyes
    shape.addEllipse(QPointF(center.x() - cellSize * 0.15, center.y() - cellSize * 0.15), cellSize * 0.1, cellSize * 0.1);
    shape.addEllipse(QPointF(center.x() + cellSize * 0.15, center.y() - cellSize * 0.15), cellSize * 0.1, cellSize * 0.1);

    // Draw the mouth
    shape.moveTo(center.x() - cellSize * 0.3, center.y() + cellSize * 0.2);
    shape.cubicTo(center.x() - cellSize * 0.2, center.y() + cellSize * 0.4, center.x() + cellSize * 0.2, center.y() + cellSize * 0.4, center.x() + cellSize * 0.3, center.y() + cellSize * 0.2);

    setPath(shape);
    // Set the center of the square to its position
    setTransformOriginPoint(boundingRect().center());

    canMove  = true;
}

// Set the object position on the grid
void Player::setGridPos(int x, int y)
{
    gridX = x;
    gridY = y;
}

int Player::getGridX()
{
    return gridX;
}

int Player::getGridY()
{
    return gridY;
}

int Player::getEnergy() const
{
    return energy;
}

bool Player::getCanMove() const
{
    return canMove;
}

void Player::energyDecrement()
{
    energy--;
}

void Player::setCanMove(bool canMove)
{
    this->canMove = canMove;
}

void Player::move(int direction)
{
    // If the game is paused, then terminate the function
    if (!canMove)
        return;

    switch (direction)
    {
    case 0:  // Up
        gridY = qMax(0, gridY - 1);
        break;
    case 1:  // Left
        gridX = qMax(0, gridX - 1);
        break;
    case 2:  // Down
        gridY = qMin(gridY + 1, gridSize - 1);
        break;
    case 3:  // Right
        gridX = qMin(gridX + 1, gridSize - 1);
        break;
    }

    // Set new coordinates on the grid
    qreal x = gridX * cellSize + 0.5 * (cellSize - boundingRect().width());
    qreal y = gridY * cellSize + 0.5 * (cellSize - boundingRect().height());
    setPos(x, y);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    // If the character is dragged, ignore the keyboard
    if (isDragging)
        return;

    switch (event->key())
    {
    case Qt::Key_W:
        move(0); // Up
        break;
    case Qt::Key_A:
        move(1); // Left
        break;
    case Qt::Key_S:
        move(2); // Down
        break;
    case Qt::Key_D:
        move(3); // Right
        break;
    }
}

// Mouse events
void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = true;
        offset = event->scenePos() - pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (isDragging)
    {
        int newGridX = qRound((event->scenePos().x() - offset.x()) / cellSize);
        int newGridY = qRound((event->scenePos().y() - offset.y()) / cellSize);

        bool isNextToPlayer = (newGridX == gridX && abs(newGridY - gridY) <= 1) ||
                              (newGridY == gridY && abs(newGridX - gridX) <= 1);

        bool isInsideGrid = newGridX >= 0 && newGridX < gridSize && newGridY >= 0 && newGridY < gridSize;

        if (isNextToPlayer && isInsideGrid)
            setPos(event->scenePos() - offset);
    }
}

void Player::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;
        setCursor(Qt::ArrowCursor);

        gridX = qRound(pos().x() / cellSize);
        gridY = qRound(pos().y() / cellSize);

        qreal x = gridX * cellSize + 0.5 * (cellSize - boundingRect().width());
        qreal y = gridY * cellSize + 0.5 * (cellSize - boundingRect().height());
        setPos(x, y);
    }
}

// Include necessary header files
#include "gameobject.h"
#include "qbrush.h"

// Initializes the shape and color of the GameObject
GameObject::GameObject(const QPainterPath& shape, const QColor& color)
    : position(0, 0), shape(shape)
{
    colors.append(color);
    setPath(shape);
    setBrush(color);
}

// Set the position of the GameObject
void GameObject::setPosition(const QPointF& position)
{
    this->position = position;
    setPos(position);
}

// Set the colors of the GameObject
void GameObject::setColors(const QList<QColor>& colors)
{
    this->colors = colors;
    setBrush(colors.first());
}


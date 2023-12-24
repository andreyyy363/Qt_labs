#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QColor>

class GameObject : public QGraphicsPathItem {
public:
    GameObject(const QPainterPath& shape, const QColor& color);

    void setPosition(const QPointF& position);
    void setColors(const QList<QColor>& colors);

protected:
    QPointF position;
    QPainterPath shape;
    QList<QColor> colors;
};

#endif // GAMEOBJECT_H

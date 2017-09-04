#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>

class ShapeItem : public QGraphicsItemGroup, public QObject
{
    const int EllipseRadius = 3;
    const int LineWidth = 1;
    QPen m_pen;
    QBrush m_brush;
public:
    ShapeItem(const QColor &color, QObject *parent = 0);
    void removePoint();
public slots:
    void addPoint(QPointF point);
    void addLine(QPointF point);
    void addRect(QPointF point);
    void addEllipse(QPointF point);
protected:
    QGraphicsEllipseItem *m_lastPoint;
    QGraphicsLineItem *line = nullptr;
    QGraphicsRectItem *rect = nullptr;
    QGraphicsEllipseItem *el = nullptr;
};

#endif // SHAPEITEM_H

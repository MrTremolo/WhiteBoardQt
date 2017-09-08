#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>

// Class for items of scene in wboard, that can create
// lines, curves, rectangles and ellipses
class ShapeItem : public QObject, public QGraphicsItemGroup
{

public:
    ShapeItem(const QColor&, const int, QObject *parent = nullptr);
    ~ShapeItem() {}

    void setFirstPoint(QPointF *point);

    void addCurve(QPointF *point);
    void addLine(QPointF *point);
    void addRect(QPointF *point);
    void addEllipse(QPointF *point);

    void removePoint();

protected:
    QPointF *m_lastPoint = nullptr;
    QGraphicsItem *currentItem = nullptr;
private:
    QPointF *calculateCoordinatesForCorrectRect(QPointF*, QPointF*);
    int penWidth;
    QPen m_pen;
    QBrush m_brush;
};

#endif // SHAPEITEM_H

#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

// Class for items of scene in wboard, that can create
// lines, curves, rectangles and ellipses
class ShapeItem : public QGraphicsItem
{
public:
	enum shape { curve, line, rectangle, ellipse };

    ShapeItem(QPointF, const QColor&, const int, shape, QGraphicsItem *parent = nullptr);
    virtual ~ShapeItem() {}

	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

	void setXYChange(QPointF*);
	
private:
    int penWidth;
    QPen pen;
	shape figure;
	QPointF firstPoint;
	QPointF changePoint;
};

#endif // SHAPEITEM_H

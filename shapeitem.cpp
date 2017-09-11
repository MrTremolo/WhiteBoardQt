#include "shapeitem.h"	
#include <QDebug>

ShapeItem::ShapeItem(QPointF pos, const QColor &color, const int width, shape sh, QGraphicsItem *parent)
    : QGraphicsItem(parent), firstPoint(pos), changePoint(pos),
	figure(sh), pen(color), penWidth(width)
{
    pen.setWidth(width);
}

QRectF ShapeItem::boundingRect() const
{
	// Curve boundingRect() is determined as childs-lines boundingRects
	if (figure == curve)
		return QRectF();

	// Line, rectangle, ellipse boundingRect() is firstly
	// normalized by m_lastPoint and changePoint 
	// to ensure that topLeft and bottomRight vertexes
	// is determined right
	else
	{
		QRectF rect(QPointF(firstPoint.x(), firstPoint.y()),
			QPointF(changePoint.x(), changePoint.y()));
		rect = rect.normalized();
		return QRectF(QPointF(rect.topLeft().x()-penWidth, rect.topLeft().y()-penWidth), 
					  QPointF(rect.bottomRight().x()+penWidth, rect.bottomRight().y() + penWidth));
	}
}

void ShapeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	// Line, rectangle, ellipse painting
	painter->setPen(pen);
	if (figure == line)
		painter->drawLine(firstPoint, changePoint);
	else if (figure == rectangle)
		painter->drawRect(QRectF(firstPoint, changePoint).normalized());
	else if (figure == ellipse)
		painter->drawEllipse(QRectF(firstPoint, changePoint).normalized());
	// Curve painting is determined by childs-lines paint()
}

void ShapeItem::setXYChange(QPointF* pos)
{
	// Line, rectangle, ellipse is painting with ShapeItem paint()
	// firstPoint is first point
	// changePoint is point from moveMouseEvent 
	if (figure != curve)
	{
		changePoint = *pos;
		prepareGeometryChange();
	}

	// Curve is consists of many childs-lines
	// changePoint is firstPoint of the new line
	// *pos is the end of new line
	else
	{
		QGraphicsLineItem *line = new QGraphicsLineItem(
			QLineF(changePoint, *pos), this
		);
		line->setPen(pen);
		changePoint = *pos;
	}
}

#include "shapeitem.h"

ShapeItem::ShapeItem(const QColor &color, const int width, QObject *parent)
    : QObject(parent), QGraphicsItemGroup(),
      m_pen(color), m_brush(color), penWidth(width)
{
    m_pen.setWidth(width);
}

void ShapeItem::setFirstPoint(QPointF *point)
{
    // Memorise coordinates of first click point
    m_lastPoint = new QPointF(point->x(), point->y());
}

void ShapeItem::addCurve(QPointF *point)
{
    // Curve is consists of lines
    if (m_lastPoint)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem(
                    QLineF(*m_lastPoint, *point), this
                    );
        line->setPen(m_pen);
        currentItem = line;

        delete m_lastPoint;
    }

    // Every time set new last click point
    m_lastPoint = new QPointF(point->x(), point->y());
}



void ShapeItem::addLine(QPointF *point)
{
    if (m_lastPoint)
    {
        if (currentItem)
        {
            removeFromGroup(currentItem);
            delete currentItem;
        }

        QGraphicsLineItem *line = new QGraphicsLineItem(
                    QLineF(*m_lastPoint, *point), this
                    );
        line->setPen(m_pen);
        currentItem = line;
    }
    else
    {
        m_lastPoint = new QPointF(point->x(), point->y());
    }
}

void ShapeItem::addRect(QPointF *point)
{
    QPointF radius(penWidth, penWidth);
    if (m_lastPoint)
    {
        if (currentItem)
        {
            removeFromGroup(currentItem);
            delete currentItem;
        }

        // There is a case when we know 2 points of rectangle but it
        // may not be the only lefttop vertex and rightbot vertex

        // coordinatesForRect returns 2 QPointfS of lefttop vertex
        // and rightbot vertex of the rectange (for correct calling constructor)
        // of QRectF
        QPointF *coordinatesForRect = calculateCoordinatesForCorrectRect(point, m_lastPoint);
        QGraphicsRectItem *rect =  new QGraphicsRectItem(QRectF(coordinatesForRect[0],
                                                               coordinatesForRect[1]),
                                                         this);
        delete[] coordinatesForRect;
        rect->setPen(m_pen);
        currentItem = rect;
    }
    else
    {
        m_lastPoint = new QPointF(point->x(), point->y());
    }
}

void ShapeItem::addEllipse(QPointF *point)
{
    QPointF radius(penWidth, penWidth);
    if (m_lastPoint)
    {
        if (currentItem)
        {
            removeFromGroup(currentItem);
            delete currentItem;
        }

        // There is a case when we know 2 points of rectangle but it
        // may not be the only lefttop vertex and rightbot vertex

        // coordinatesForRect returns 2 QPointfS of lefttop vertex
        // and rightbot vertex of the rectange (for correct calling constructor)
        // of QRectF
        QPointF *coordinatesForRect = calculateCoordinatesForCorrectRect(point, m_lastPoint);
        QGraphicsEllipseItem *el = new QGraphicsEllipseItem(QRectF(coordinatesForRect[0],
                                                                   coordinatesForRect[1]), this);
        delete[] coordinatesForRect;
        el->setPen(m_pen);
        currentItem = el;
    }
    else
    {
        m_lastPoint = new QPointF(point->x(), point->y());
    }
}

void ShapeItem::removePoint()
{
    // Delete coordinates of first click point
    if (m_lastPoint)
        delete m_lastPoint;
    m_lastPoint = nullptr;
}

// Returns topleft and rightbot vertex of rect, that consists of pos1 and pos2 vertexes
QPointF *ShapeItem::calculateCoordinatesForCorrectRect(QPointF *pos1, QPointF *pos2)
{
    QPointF *coordinates = new QPointF[2];

    if (pos1->x() < pos2->x())
    {
        coordinates[0].setX(pos1->x());
        coordinates[1].setX(pos2->x());
    }
    else
    {
        coordinates[0].setX(pos2->x());
        coordinates[1].setX(pos1->x());
    }
    if (pos1->y() < pos2->y())
    {
        coordinates[0].setY(pos1->y());
        coordinates[1].setY(pos2->y());
    }
    else
    {
        coordinates[0].setY(pos2->y());
        coordinates[1].setY(pos1->y());
    }

    return coordinates;
}



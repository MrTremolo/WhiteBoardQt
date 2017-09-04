#include "shapeitem.h"
#include <QDebug>

ShapeItem::ShapeItem(const QColor &color, QObject *parent)
    : QGraphicsItemGroup(), QObject(parent),
      m_pen(color), m_brush(color), m_lastPoint(nullptr)
{
    m_pen.setWidth(LineWidth);
}

void ShapeItem::removePoint()
{
    if (m_lastPoint)
        delete m_lastPoint;
    m_lastPoint = nullptr;
}

void ShapeItem::addPoint(QPointF point)
{
    QPointF radius(EllipseRadius, EllipseRadius);

    if (m_lastPoint)
    {
        line = new QGraphicsLineItem(
                    QLineF(m_lastPoint->pos(), point), this
                    );
        line->setPen(m_pen);
        delete m_lastPoint;
    }
    m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius));
    m_lastPoint->setBrush(m_brush);
    m_lastPoint->setPos(point);
}

void ShapeItem::addLine(QPointF point)
{
    QPointF radius(EllipseRadius, EllipseRadius);
    qDebug() << "ska";
    if (m_lastPoint)
    {
        if (line)
        {
            removeFromGroup(line);
            delete line;
        }
        line = new QGraphicsLineItem(
                    QLineF(m_lastPoint->pos(), point), this
                    );
        line->setPen(m_pen);
        //delete m_lastPoint;
    }
    else
    {
        m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius));
        m_lastPoint->setBrush(m_brush);
        m_lastPoint->setPos(point);
    }
}

void ShapeItem::addRect(QPointF point)
{
    QPointF radius(EllipseRadius, EllipseRadius);
    qDebug() << "rect";
    if (m_lastPoint)
    {
        if (rect)
        {
            removeFromGroup(rect);
            delete rect;
        }
        rect = new QGraphicsRectItem(QRectF(m_lastPoint->pos(), point), this);
        rect->setPen(m_pen);
        //delete m_lastPoint;
    }
    else
    {
        m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius));
        m_lastPoint->setBrush(m_brush);
        m_lastPoint->setPos(point);
    }
}

void ShapeItem::addEllipse(QPointF point)
{
    QPointF radius(EllipseRadius, EllipseRadius);
    qDebug() << "el";
    if (m_lastPoint)
    {
        if (el)
        {
            removeFromGroup(el);
            delete el;
        }
        el = new QGraphicsEllipseItem(QRectF(m_lastPoint->pos(), point), this);
        el->setPen(m_pen);
        //delete m_lastPoint;
    }
    else
    {
        m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius));
        m_lastPoint->setBrush(m_brush);
        m_lastPoint->setPos(point);
    }
}



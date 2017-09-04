#include "view.h"
#include "shapeitem.h"
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDebug>

View::View(int h, int w, QWidget *parent) :
    QGraphicsView(parent), m_scene(0, 0, 300, 400, this),
    m_isKeyPressed(false)
{
    setScene(&m_scene);
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}

void View::resizeEvent(QResizeEvent *event)
{
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}


void View::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = mapToScene(event->pos());

        ShapeItem *si = new ShapeItem(QColor(123, 127, 0), &m_scene);
        m_line.push_back(si);
        m_scene.addItem(m_line.back());
        if (state == "Curve")
            m_line.back()->addPoint(pos);
        else if (state == "Line")
            m_line.back()->addLine(pos);
        else if (state == "Rectangle")
            m_line.back()->addRect(pos);
        else if (state == "Ellipse")
            m_line.back()->addEllipse(pos);
        m_isKeyPressed = true;
    }
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isKeyPressed)
    {
        QPointF pos = mapToScene(event->pos());
        if (state == "Curve")
            m_line.back()->addPoint(pos);
        else if (state == "Line")
            m_line.back()->addLine(pos);
        else if (state == "Rectangle")
            m_line.back()->addRect(pos);
        else if (state == "Ellipse")
            m_line.back()->addEllipse(pos);
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isKeyPressed = false;
        m_line.back()->removePoint();
    }
}

void View::undo()
{
    qDebug() << "undo view";
    m_scene.removeItem(m_line.back());
    m_line.pop_back();
}

void View::changeState(QString str)
{
    state = str;
    qDebug() << str;
}


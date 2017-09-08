#include "view.h"
#include "shapeitem.h"
#include "scene.h"


View::View(QWidget *parent) :
    QGraphicsView(parent),
    m_isKeyPressed(false)
{
    resize(600, 300);
}

void View::setScene(Scene *scene)
{
    // View will notify scene for mouse events
    connect(this, SIGNAL(pressSignal(QPointF*)), scene, SLOT(pressEvent(QPointF*)));
    connect(this, SIGNAL(moveSignal(QPointF*)), scene, SLOT(moveEvent(QPointF*)));
    connect(this, SIGNAL(releaseSignal()), scene, SLOT(releaseEvent()));

    QGraphicsView::setScene(scene);
}

void View::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}


void View::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // On start of drawing View will notify scene of it
        // (when mouse is clicked)
        QPointF pos = mapToScene(event->pos());
        emit pressSignal(&pos);
        m_isKeyPressed = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    // Let's return the event when position of mouse is out of View
    if (!QRectF(QPoint(0, 0), size()).contains(event->localPos()))
    {
        return;
    }
    if (m_isKeyPressed)
    {
        // Otherwise View will notify scene of resume drawing
        QPointF pos = mapToScene(event->pos());
        emit moveSignal(&pos);
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // View will notify scene of stop drawing
        QPointF pos = mapToScene(event->pos());
        emit releaseSignal();
        m_isKeyPressed = false;

    }
}




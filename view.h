#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include <QPointF>
#include <QSizeF>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsView>

class Scene;

class ShapeItem;

// Class for graphicsview of wboard
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);
    void setScene(Scene *scene);

protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:   
    void pressSignal(QPointF*);
    void moveSignal(QPointF*);

private:
    bool m_isKeyPressed;
};

#endif // VIEW_H

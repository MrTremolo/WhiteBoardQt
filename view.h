#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>

class ShapeItem;

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(int h, int w, QWidget *parent = 0);

public slots:
    void resizeEvent(QResizeEvent *event);
    void undo();
    void changeState(QString);
protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected:
    QGraphicsScene m_scene;
    QVector<ShapeItem*> m_line;
    bool m_isKeyPressed;
private:
    QString state = "Curve";
};

#endif // VIEW_H

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class ShapeItem;

// Class for scene of wboard
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(int h, int w, QObject *parent = nullptr);
    ~Scene() {}

signals:
    // Signals for notifing View to disable or enable buttons
    void turnRedo(bool);
    void turnUndo(bool);

public slots:
    // Slots from View of mouse events
    void pressEvent(QPointF*);
    void moveEvent(QPointF*);
    void releaseEvent();

    // Slots from View of changing special tools
    void changeState(const QString&);
    void changeColor(const QString&);
    void changeWidth(int);

    // Push-buttons
    void undo();
    void redo();
    void clearAll();

private:
    QString state = "Curve";
    QString color = "#000000";
    int penWidth = 1;
    ShapeItem *currentItem;

    // Painted elements
    QList<QGraphicsItem*> sceneItems;

    // Deleted elements on click undo button
    // It has to be to ability to readd elements
    QList<QGraphicsItem*> trashItems;

};

#endif // SCENE_H

#include "scene.h"
#include "shapeitem.h"


Scene::Scene(int h, int w, QObject *parent) : QGraphicsScene(0, 0, h, w, parent)
{

}

void Scene::pressEvent(QPointF *pos)
{
    // Current Item that painted and will modified
    currentItem = new ShapeItem(QColor(color), penWidth, this);
    currentItem->setFirstPoint(pos);
    sceneItems.push_back(currentItem);
    addItem(currentItem);

    // Clear trashItems list
    if (trashItems.size())
    {
        for (auto i = trashItems.begin(); i != trashItems.end(); i++)
            delete *i;
        trashItems.clear();
    }

    emit turnRedo(false);
    emit turnUndo(true);
}

void Scene::moveEvent(QPointF *pos)
{
    if (state == "Curve")
    { 
        currentItem->addCurve(pos);
    }
    else if (state == "Line")
    {
        currentItem->addLine(pos);
    }
    else if (state == "Rectangle")
    {
        currentItem->addRect(pos);
    }
    else if (state == "Ellipse")
    {
        currentItem->addEllipse(pos);
    }
}

void Scene::releaseEvent()
{
    currentItem->removePoint();
}

void Scene::undo()
{
    // On click undo button
    if (sceneItems.size())
    {
        QGraphicsItem *item = sceneItems.back();
        trashItems.push_back(item);
        sceneItems.pop_back();
        removeItem(item);
        emit turnRedo(true);
        if (!sceneItems.size())
            emit turnUndo(false);
    }

}

void Scene::redo()
{
    // On click redo button
    if (trashItems.size())
    {
        addItem(trashItems.back());
        sceneItems.push_back(trashItems.back());
        trashItems.pop_back();
        emit turnUndo(true);
        if (!trashItems.size())
            emit turnRedo(false);
    }

}

void Scene::clearAll()
{
    // On click clearAll button
    clear();

    for (auto i = sceneItems.begin(); i != sceneItems.end(); i++)
        delete *i;
    for (auto j = trashItems.end(); j != trashItems.end(); j++)
        delete *j;
    sceneItems.clear();
    trashItems.clear();

    emit turnUndo(false);
    emit turnRedo(false);
}

void Scene::changeState(const QString &str)
{
    state = str;
}

void Scene::changeColor(const QString & str)
{
    color = str;
}

void Scene::changeWidth(int width)
{
    penWidth = width;
}

#include "scene.h"	
#include "shapeitem.h"


Scene::Scene(int h, int w, QObject *parent) : QGraphicsScene(0, 0, h, w, parent)
{

}

void Scene::pressEvent(QPointF *pos)
{
    // Current Item that painted and will modified
	
	if (state == "Curve")
		currentItem = new ShapeItem(*pos, QColor(color), penWidth, ShapeItem::curve);
	if (state == "Line")
		currentItem = new ShapeItem(*pos, QColor(color), penWidth, ShapeItem::line);
	else if (state == "Rectangle")
		currentItem = new ShapeItem(*pos, QColor(color), penWidth, ShapeItem::rectangle);
	else if (state == "Ellipse")
		currentItem = new ShapeItem(*pos, QColor(color), penWidth, ShapeItem::ellipse);
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
	currentItem->setXYChange(pos);
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
	// delete shown elements
    clear();

    sceneItems.clear();

	// delete elements in trash
	for (auto i = trashItems.begin(); i != trashItems.end(); i++)
		delete *i;
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

Scene::~Scene()
{
	// delete shown elements
	clear();

	// delete elements in trash
	for (auto i = trashItems.begin(); i != trashItems.end(); i++)
		delete *i;
}

#include "wboard.h"
#include "MyToolBar.h"
#include "view.h"
#include "scene.h"
#include "aspectratiowidget.h"

wboard::wboard(QWidget *parent) :
    QMainWindow(parent),
    scene(new Scene(800, 400, this)),
    viewport(new View(this)),
    toolBar(new MyToolBar(scene, this))

{   
    addToolBar(Qt::TopToolBarArea, toolBar);

    // Create additional widget-wrapper for fixing viewport with its ratio size
    AspectRatioWidget *w = new AspectRatioWidget(viewport, 2, 1, this);
    setCentralWidget(w);

    viewport->setScene(scene);
}

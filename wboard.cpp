#include "wboard.h"
#include "MyToolBar.h"
#include "view.h"
#include <QGraphicsView>


wboard::wboard(QWidget *parent) :
    QMainWindow(parent),
    viewport(new View(300, 400)),
    mtb(new MyToolBar(viewport))
{
    addToolBar(Qt::TopToolBarArea, mtb);

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(mtb);
    vbl->addWidget(viewport);

    QWidget *window = new QWidget;
    window->setLayout(vbl);

    setCentralWidget(window);


}
wboard::~wboard()
{

}

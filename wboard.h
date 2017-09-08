#ifndef WBOARD_H
#define WBOARD_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QResizeEvent>

class View;

class MyToolBar;

class Scene;

// The main widget class
class wboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit wboard(QWidget *parent = 0);
    ~wboard() {}

private:
    Scene* scene;
    View* viewport;
    MyToolBar* toolBar;

};

#endif // WBOARD_H

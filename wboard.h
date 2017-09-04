#ifndef WBOARD_H
#define WBOARD_H

#include <QMainWindow>

class View;

class MyToolBar;

class wboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit wboard(QWidget *parent = 0);
    ~wboard();

private:
    View* viewport;
    MyToolBar* mtb;


};

#endif // WBOARD_H

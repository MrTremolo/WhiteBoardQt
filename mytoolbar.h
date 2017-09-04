#ifndef MYTOOLBAR_H
#define MYTOOLBAR_H
#include <QToolBar>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QSignalMapper>

class View;

class MyToolBar : public QToolBar
{
    Q_OBJECT

public:
    MyToolBar(View* view, QWidget* parent = 0);
    ~MyToolBar() {
        delete colorWidgets;
    }
private:
    View *viewport;
    QWidget* toolBar;
    QWidget* firstRow;
    QWidget* secondRow;

    QWidget* palet;
    QSlider* slider;
    QSpinBox* spinBox;

    QWidget* currentColor;
    QVector<QPushButton> *colorWidgets;

    QComboBox* comboBox;
    QPushButton* pushButton1;
    QPushButton* pushButton2;
    QPushButton* pushButton3;
    const QVector<QColor> colors = { QColor(255, 0, 0), QColor(0, 255, 0), QColor(0, 0, 255),
                                     QColor(255, 255, 0), QColor(0, 255, 255), QColor(255, 0, 255),
                                     QColor(0, 0, 0), QColor(76, 55, 9), QColor(128, 128, 128),
                                     QColor(128, 128, 75), QColor(0, 70, 128), QColor(128, 55, 55),
                                     QColor(252, 65, 11), QColor(32, 33, 89), QColor(65, 222, 200),
                                     QColor(129, 12, 205)
                                    };

    void createFirstRow();
    void createPalette();
    void createSecondRow();

public slots:
    void colorButtonClicked(const QString&);
};

#endif // MYTOOLBAR_H

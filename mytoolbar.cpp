#include "mytoolbar.h"
#include "view.h"



MyToolBar::MyToolBar(View* view, QWidget* parent) : QToolBar(parent), viewport(view)
{
    this->setMovable(false);
    this->setMinimumSize(450, 100);

    toolBar = new QWidget(this);
    toolBar->setMinimumSize(450, 100);

    QVBoxLayout* vbl = new QVBoxLayout(toolBar);
    vbl->setSpacing(5);
    vbl->setContentsMargins(10, 5, 10, 5);

    createFirstRow();

    createSecondRow();

    vbl->addWidget(firstRow);
    vbl->addWidget(secondRow);


}

void MyToolBar::createFirstRow()
{
    firstRow = new QWidget(toolBar);
    QHBoxLayout* hblayout = new QHBoxLayout(firstRow);
    hblayout->setSpacing(15);
    hblayout->setMargin(0);

    QLabel* labelFirstRow = new QLabel("Pen Color:");

    createPalette();

    QLabel* labelFirstRowPenSize = new QLabel("Pen Size:");

    slider = new QSlider(Qt::Horizontal, firstRow);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setRange(1, 9);
    slider->setPageStep(2);

    spinBox = new QSpinBox(firstRow);
    spinBox->setRange(1, 9);

    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    hblayout->addWidget(labelFirstRow);
    hblayout->addWidget(palet);
    hblayout->addWidget(labelFirstRowPenSize);
    hblayout->addWidget(slider);
    hblayout->addWidget(spinBox);
    hblayout->addStretch(1);
}

void MyToolBar::createPalette()
{
    palet = new QWidget(firstRow);
    palet->setFixedSize(159, 31);

    QHBoxLayout* horizontalLayout = new QHBoxLayout(palet);
    horizontalLayout->setSpacing(1);
    horizontalLayout->setMargin(0);


    QGridLayout *grid = new QGridLayout;
    grid->setHorizontalSpacing(1);
    grid->setVerticalSpacing(1);
    grid->setContentsMargins(0, 0, 0, 0);


    currentColor = new QWidget(palet);
    QPalette currentColorPalette;
    currentColorPalette.setColor(currentColor->backgroundRole(), Qt::black);
    currentColor->setPalette(currentColorPalette);
    currentColor->setAutoFillBackground(true);
    horizontalLayout->addWidget(currentColor);
    currentColor->setFixedSize(30, 31);

    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(const QString&)), SLOT(colorButtonClicked(const QString&)));
    for (int i = 0; i < 16; ++i)
    {
        QPushButton *colorButton = new QPushButton(palet);
        colorButton->setStyleSheet(QString("background-color: %1").arg(colors[i].name()));
        grid->addWidget(colorButton, i / 8, i % 8, 1, 1);
        connect(colorButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(colorButton, colors[i].name());
    }
    horizontalLayout->addLayout(grid);
}

void MyToolBar::createSecondRow()
{
    secondRow = new QWidget(toolBar);
    QHBoxLayout* hblayout = new QHBoxLayout(secondRow);
    hblayout->setSpacing(15);
    hblayout->setMargin(0);

    QLabel* labelSecondRow = new QLabel("Shape:", secondRow);
    labelSecondRow->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));


    QComboBox* comboBox = new QComboBox(secondRow);
    QStringList lst;
    lst << "Curve" << "Line" << "Rectangle" << "Ellipse";
    comboBox->addItems(lst);
    connect(comboBox, SIGNAL(activated(QString)), viewport, SLOT(changeState(QString)));


    QPushButton* pushButton1 = new QPushButton("undo", secondRow);
    connect(pushButton1, SIGNAL(clicked(bool)), viewport, SLOT(undo()));
    QPushButton* pushButton2 = new QPushButton("redo", secondRow);
    QPushButton* pushButton3 = new QPushButton("cleanup", secondRow);

    hblayout->addWidget(labelSecondRow);
    hblayout->addWidget(comboBox);
    hblayout->addWidget(pushButton1);
    hblayout->addWidget(pushButton2);
    hblayout->addWidget(pushButton3);
    hblayout->addStretch(1);

}

void MyToolBar::colorButtonClicked(const QString &str)
{
    currentColor->setStyleSheet("background-color: " + str);
    qDebug() << str;
}


#include "mytoolbar.h"
#include "scene.h"


MyToolBar::MyToolBar(Scene* sceneArg, QWidget* parent) : QToolBar(parent), scene(sceneArg)
{

    // Constructing of toolBar is divided to construct elements of first and second row
    // ToolBar has fixed height with ability to stretch in width
    this->setMovable(false);
    this->setFixedHeight(100);
    this->setMinimumWidth(450);

    toolBar = new QWidget(this);
    toolBar->setFixedSize(450, 100);

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
    // Wrapper-widget for first row elements
    firstRow = new QWidget(toolBar);

    QHBoxLayout* hblayout = new QHBoxLayout(firstRow);
    hblayout->setSpacing(15);
    hblayout->setMargin(0);

    firstLabelOfFirstRow = new QLabel("Pen Color:", firstRow);

    // Create pallete of picking color
    createPalette();

    secondLabelOfFirstRow = new QLabel("Pen Size:", firstRow);

    slider = new QSlider(Qt::Horizontal, firstRow);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setRange(1, 9);
    slider->setPageStep(2);

    spinBox = new QSpinBox(firstRow);
    spinBox->setRange(1, 9);

    // Bind changing of slider and spinBox beetween itself
    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    // Also we will notify the scene about this
    connect(slider, SIGNAL(valueChanged(int)), scene, SLOT(changeWidth(int)));

    hblayout->addWidget(firstLabelOfFirstRow);
    hblayout->addWidget(palet);
    hblayout->addWidget(secondLabelOfFirstRow);
    hblayout->addWidget(slider);
    hblayout->addWidget(spinBox);
}

void MyToolBar::createPalette()
{
    palet = new QWidget(firstRow);
    palet->setFixedSize(159, 31);

    QHBoxLayout* horizontalLayout = new QHBoxLayout(palet);
    horizontalLayout->setSpacing(1);
    horizontalLayout->setMargin(0);

    // GridLayout for small squares-buttons
    QGridLayout *grid = new QGridLayout();
    grid->setHorizontalSpacing(1);
    grid->setVerticalSpacing(1);
    grid->setContentsMargins(0, 0, 0, 0);

    // Big square, that tracks changes of picking small color buttons
    // If the user push a color button, it will change color to color of button
    currentColor = new QWidget(palet);
    QPalette currentColorPalette;
    currentColorPalette.setColor(currentColor->backgroundRole(), Qt::black);
    currentColor->setPalette(currentColorPalette);
    currentColor->setAutoFillBackground(true);
    horizontalLayout->addWidget(currentColor);
    currentColor->setFixedSize(30, 31);

    // SignalMapper transmits colors of button on click them
    // to Big square(currentColor) and scene
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(const QString&)), SLOT(colorButtonClicked(const QString&)));
    connect(signalMapper, SIGNAL(mapped(const QString&)), scene, SLOT(changeColor(const QString&)));
    for (int i = 0; i < 16; ++i)
    {
        QPushButton *colorButton = new QPushButton(palet);

        // Color of buttons is taken from const vector of colors
        // in the initializer-list of class
        colorButton->setStyleSheet(QString("background-color: %1").arg(colors[i].name()));
        grid->addWidget(colorButton, i / 8, i % 8, 1, 1);
        connect(colorButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(colorButton, colors[i].name());
    }
    horizontalLayout->addLayout(grid);

}

void MyToolBar::createSecondRow()
{
    // Wrapper-widget for second row elements
    secondRow = new QWidget(toolBar);

    QHBoxLayout* hblayout = new QHBoxLayout(secondRow);
    hblayout->setSpacing(15);
    hblayout->setMargin(0);

    firstLabelOfSecondRow = new QLabel("Shape:", secondRow);

    QComboBox* comboBox = new QComboBox(secondRow);
    QStringList lst;
    lst << "Curve" << "Line" << "Rectangle" << "Ellipse";
    comboBox->addItems(lst);
    connect(comboBox, SIGNAL(activated(const QString&)), scene, SLOT(changeState(const QString&)));

    // Toolbar will notify scene on click of special pushButtons
    // and Scene will notify toolbar when it has to be disabled or enabled
    QPushButton* pushButton1 = new QPushButton("undo", secondRow);
    pushButton1->setEnabled(false);
    connect(pushButton1, SIGNAL(clicked(bool)), scene, SLOT(undo()));
    connect(scene, SIGNAL(turnUndo(bool)), pushButton1, SLOT(setEnabled(bool)));
    QPushButton* pushButton2 = new QPushButton("redo", secondRow);
    pushButton2->setEnabled(false);
    connect(pushButton2, SIGNAL(clicked(bool)), scene, SLOT(redo()));
    connect(scene, SIGNAL(turnRedo(bool)), pushButton2, SLOT(setEnabled(bool)));
    QPushButton* pushButton3 = new QPushButton("cleanup", secondRow);
    connect(pushButton3, SIGNAL(clicked(bool)), scene, SLOT(clearAll()));

    hblayout->addWidget(firstLabelOfSecondRow);
    hblayout->addWidget(comboBox);
    hblayout->addWidget(pushButton1);
    hblayout->addWidget(pushButton2);
    hblayout->addWidget(pushButton3);

}

void MyToolBar::colorButtonClicked(const QString &str)
{
    // Set color of big square
    currentColor->setStyleSheet("background-color: " + str);
}


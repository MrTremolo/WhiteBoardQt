#include "wboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	
    QApplication a(argc, argv);

    wboard w;
    w.show();

    return a.exec();
}

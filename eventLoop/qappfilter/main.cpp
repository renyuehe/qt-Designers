#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Filter *filter = new Filter;
    a.installEventFilter(filter);

    Widget w;
    w.show();

    return a.exec();
}

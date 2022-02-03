#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    Filter filter;
    a.installEventFilter(&filter);
#endif

    Widget w;
    w.show();

    return a.exec();
}

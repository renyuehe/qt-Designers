#include "widget.h"
#include <QApplication>

#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QTableView view;
    view.hideColumn(3);

    return a.exec();
}

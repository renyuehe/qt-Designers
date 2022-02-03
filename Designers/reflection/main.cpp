#include <QApplication>

#include "MyInvoke.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyInvoke invoke;
    invoke.fun1("MyInvokeTest1");
    invoke.fun1("MyInvokeTest2");

    return a.exec();
}



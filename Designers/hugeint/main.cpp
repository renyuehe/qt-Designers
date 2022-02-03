#include <QCoreApplication>
#include "hugeint.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HugeInt num(2000880000);
    num.show();

    return a.exec();
}

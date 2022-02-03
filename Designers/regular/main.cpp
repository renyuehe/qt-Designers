#include <QApplication>
#include <QLineEdit>

#include "HRegExpManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRegExpValidator * valid = HRegExpManager::getInstance()->getUrlValidator();

    QLineEdit *edit = new QLineEdit();
    edit->setValidator(valid);

    return a.exec();
}

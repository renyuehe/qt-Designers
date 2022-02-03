#include "textbook.h"
#include <QMap>
#include <QDebug>

TextbookMap::~TextbookMap() {
    qDebug() << "Destroying TextbookMap ..." << endl;
    qDeleteAll(values());
    clear(); 
}

void TextbookMap::add(Textbook* text) {
}

QString TextbookMap::toString() const {
    QString retval;
    QTextStream os(&retval);
    ConstIterator itr = constBegin();
    for ( ; itr != constEnd(); ++itr)
        os << '[' << itr.key() << ']' << ": "
        << itr.value()->toString() << endl;
    return retval;
}


QString Textbook::toString() const
{
    return QString("....");
}

#ifndef _TEXTBOOK_H_
#define _TEXTBOOK_H_

#include <QObject>
#include <QString>
#include <QMap>

class Textbook : public QObject {
    Q_OBJECT
  public:
    Textbook(QString title, QString author, QString isbn, uint year);

    QString toString() const;

private:
    uint m_YearPub;
    QString m_Title, m_Author, m_Isbn;
};

/* Managed collection of pointers */
class TextbookMap : public QMap<QString, Textbook*> {
  public:
    ~TextbookMap();
    /** Adds the TextBook to the map, keyed on the ISBN */
    void add(Textbook* text);
    QString toString() const;
};
#endif

#if 1

#include <QDebug>
#include <QString>
#include "stack.h"

int main() {
    Stack<int> intstack1, intstack2;
    int val;
    for (val = 0; val < 4; ++val) {
        intstack1.push(val);
        intstack2.push(2 * val);
    }
    while (intstack1.count()) {
        val = intstack1.pop();
        qDebug() << val;
    }
    Stack<QString> stringstack;
    stringstack.push("First on");
    stringstack.push("second on");
    stringstack.push("first off");
    QString val2;
    while (stringstack.count()) {
        val2 = stringstack.pop();
        qDebug() << val2;
    }
    qDebug() << "Now intstack2 will self destruct.";
    return 0;
}

#elif 0  /* Some simple examples using QStringList, split and join */

#include <QStringList>
#include <QDebug>
int main() {
    QString winter = "December, January, February";
    QString spring = "March, April, May";
    QString summer = "June, July, August";
    QString fall = "September, October, November";

    QStringList list;
    list << winter;        /* Append operator 1. */
    list += spring;        /* Append operator 2. */
    list.append(summer);   /* append member function. */
    list << fall;
    qDebug() << "The Spring months are: " << list[1] ;

    QString allmonths = list.join(", ");            /* From list to string - join with a ", " delimiter. */
    qDebug() << allmonths;

    QStringList list2 = allmonths.split(", ");      /* Split is the opposite of join. Each month will have its own element. */

    Q_ASSERT(list2.size() == 12);                   /* Q_ASSERTions abort the program
        if the condition is not satisfied. */

    foreach (const QString &str, list) {            /* Qt foreach loop - similar
      to Perl/Python and Java 1.5  style for loops. */
        qDebug() << QString(" [%1] ").arg(str);
    }

    for (QStringList::iterator it = list.begin();
         it != list.end(); ++it) {          /* C++ STL-style iteration. */
        QString current = *it;              /* Pointer-style dereference. */
        qDebug() << "[[" << current << "]]";
    }

    QListIterator<QString> itr (list2);     /* Java 1.2 style Iterator. */
    while (itr.hasNext()) {                 /* Java Iterators point between elements. */
        QString current = itr.next();
        qDebug() << "{" <<  current << "}";
    }
    return 0;
}


#elif 0 /* Some simple examples QMap */
#include <textbook.h>
#include <QDebug>

int main() {
    Textbook* t1 = new Textbook("The C++ Programming Language",
        "Stroustrup", "0201700735", 1997);
    Textbook* t2 = new Textbook("XML in a Nutshell",
        "Harold","0596002920", 2002);
    Textbook* t3 = new Textbook("UML Distilled",
        "Fowler", "0321193687", 2004);
    Textbook* t4 = new Textbook("Design Patterns", "Gamma",
        "0201633612",1995);
    { /* Inner block for demonstration purposes */
        TextbookMap m;
        m.add(t1);
        m.add(t2);
        m.add(t3);
        m.add(t4);
        qDebug() << m.toString();
        m.remove (t3->getIsbn());  /* Removed but not deleted */
    } /* End of block - local variables destroyed */
    qDebug() << "After m has been destroyed we still have:\n"
        << t3->toString();
    return 0;
}

#elif 0 /* Some simple examples qSort list */
#include <caseignorestring.h>

int main() {
    CaseIgnoreString s1("Apple"), s2("bear"),
                     s3 ("CaT"), s4("dog"), s5 ("Dog");

    Q_ASSERT(s4 == s5);
    Q_ASSERT(s2 < s3);
    Q_ASSERT(s3 < s4);

    QList<CaseIgnoreString> namelist;

    namelist << s5 << s1 << s3 << s4 << s2; /* Insert
        all items in an order that is definitely not sorted. */

    qSort(namelist.begin(), namelist.end());
    int i=0;
    foreach (const QString &stritr, namelist) {
        qDebug() << QString("namelist[%1] = %2")
                       .arg(i++).arg(stritr) ;
    }

    QStringList strlist;
    strlist << s5 << s1 << s3 << s4 << s2; /* The value
       collection holds QString but, if you add CaseIgnoreString,
       a conversion is required. */

    qSort(strlist.begin(), strlist.end());
    qDebug() << "StringList sorted: " + strlist.join(", ");
    return 0;
}

#endif

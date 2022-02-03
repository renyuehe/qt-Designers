#ifndef SQLSTR_H
#define SQLSTR_H

#include "DB_Operation_global.h"
#include <QString>
#include "sqlgenerator.h"

class SqlStr{
public:
    SqlStr(){}
    ~SqlStr(){}
    QString m_sSsqlStr;

    template <typename ...Args>
    SqlStr& select(QString tableName, Args... qstrings)
    {
        m_sSsqlStr += SqlGenerator::selectGerner(tableName, qstrings...);
        return *this;
    }

    template <typename ...Args>
    SqlStr& where(Args... qstrings)
    {
        m_sSsqlStr += SqlGenerator::whereGerner(qstrings...);
        return *this;
    }

public:
    friend QDebug operator<<(QDebug dbg, SqlStr &sqlObj)
    {
     const QString body = sqlObj.m_sSsqlStr;

     QVector<QStringRef> pieces = body.splitRef("\r\n", QString::SkipEmptyParts);
     if (pieces.isEmpty())
         dbg.nospace() << "SqlGenerator()";
     else if (pieces.size() == 1)
         dbg.nospace() << "SqlGenerator(" << pieces.first() << ")";
     else
         dbg.nospace() << "SqlGenerator(" << pieces.first() << " ...)";
     return dbg.maybeSpace();
    }
};

#endif // SQLSTR_H

#ifndef SQLGENERATOR_H
#define SQLGENERATOR_H

#include <QDateTime>
#include <QVariant>
#include <QDebug>


#include "DB_Operation_global.h"

//需要解决 qDebug()操作方式 或者QString操作方式比如 << << <<  .arg.arg.arg

class SqlGenerator{
public:
    static SqlGenerator * getInstance();
    ~SqlGenerator(){}

    /***********************************/
private:


    /**
     * @brief 表的数据结构转义,把 QVariant的值 传给 模板T
     * @param [in]传入值
     * @param [in,out]获得传入值
     */
    template<typename T>
    static void  assignToStr(T &t, QString &str) //const
    {
        const static size_t __intID = typeid (int).hash_code();
        const static size_t __uintID = typeid (unsigned int).hash_code();
        const static size_t __boolID = typeid (bool).hash_code();
        const static size_t __doubleID = typeid (double).hash_code();
        const static size_t __floatID = typeid (float).hash_code();
        const static size_t __llID = typeid (long long).hash_code();
        const static size_t __ullID = typeid (unsigned long long).hash_code();
        const static size_t __charId = typeid (char).hash_code();
        const static size_t __QStringID = typeid (QString).hash_code();
        const static size_t __QDateTimeID = typeid (QDateTime).hash_code();
        const static size_t __QDateID = typeid (QDate).hash_code();
        const static size_t __QTimeID = typeid (QTime).hash_code();
        const static size_t __QByteArrayID = typeid (QByteArray).hash_code();

        const size_t id = (typeid (t).hash_code());//获得 t 的  type hashCode

        T *p = &t;
        if(id == __intID)
        {
           //qDebug() << "__intID" << __LINE__ << __func__;
            str = QString::number(*(int *)p);
        }
        else if(id == __uintID)
        {
           //qDebug() << "__uintID"  << __LINE__ << __func__;
           str = QString::number(*(unsigned int *)p);
        }
        else if(id == __boolID)
        {
            //qDebug() << "__boolID"  << __LINE__ << __func__;
            str = QString::number(*(bool *)p);
        }
        else if(id == __doubleID)
        {
            //qDebug() << "__doubleID"  << __LINE__ << __func__;
            str = QString::number(*(double *)p);
        }
        else if(id == __floatID)
        {
            //qDebug() << "__floatID"  << __LINE__ << __func__;
            str = QString::number(*(float *)p);
        }
        else if(id == __llID)
        {
            //qDebug() << "__llID"  << __LINE__ << __func__;
            str = QString::number(*(long long *)p);
        }
        else if(id == __ullID)
        {
            //qDebug() << "__ullID"  << __LINE__ << __func__;
            str = QString::number(*(unsigned long long *)p);
        }
        else if (id == __charId) {
            //qDebug() << "__charId"  << __LINE__ << __func__;
            str = QString(*(char *)p);
        }
        else if(id == __QStringID)
        {
            //qDebug() << "__QStringID"  << __LINE__ << __func__;
            str = *(QString *)p;
        }
        else if(id == __QDateTimeID)
        {
            //qDebug() << "__QDateTimeID"  << __LINE__ << __func__;
            (*(QDateTime *)p);
        }
        else if(id == __QDateID)
        {
            //qDebug() << "__QDateID"  << __LINE__ << __func__;
            (*(QDate *)p);
        }
        else if(id == __QTimeID)
        {
            //qDebug() << "__QTimeID"  << __LINE__ << __func__;
            (*(QTime *)p);
        }
        else if(id == __QByteArrayID)
        {
            //qDebug() << "__QByteArrayID"  << __LINE__ << __func__;
            (*(QByteArray *)p);
        }
        else {
            //qDebug() << QStringLiteral("字符串常量 ")  << __LINE__ << __func__;
#if 0 //该方式的问题模板会生成多分函数,但是有些地方是不能转换的,比如(char *)double就会错误
            char * result = (char *)t;
            str = QString(result);
#endif
            QVariant var(t);
            str = var.toString();

        }
    }

    //


    template <typename T>
    static void  commaMerge(T &t, QString &fields)
    {
        QString str;
        assignToStr(t, str);

        fields += "," + str;
    }

    template <typename T>
    static void andMerge(T &t, QString &fields){
        QString str;
        assignToStr(t, str);

        fields += " and " + str;
    }

    /** 一次性将sql全部传入方式？？？ 答:比如 Args... qstrings 那么传入参数写法为 qstrings... ***/
    template <typename ...Args>
    static void sqlMerge(Args... qstrings, QString &fields){
        int arr[] = {(commaMerge(qstrings, fields),0)...};
        fields = fields.mid(1);
    }

public:
    template <typename ...Args>
    static QString selectGerner(QString tableName, Args... qstrings)
    {
        QString fields;
        //实现func(int number)函数对 args 的遍历
        int arr[] = {(commaMerge(qstrings, fields),0)...};//args的个数决定了func(int number)函数调用次数，也决定了数组开辟多少空间，数组中存放的值则是 参数
        fields = fields.mid(1);

        QString result = QString("SELECT %1 FROM %2").arg(fields).arg(tableName);
        return result;
    }

    template <typename ...Args>
    static QString whereGerner(Args... qstrings)
    {
        QString fields;
        //实现func(int number)函数对 args 的遍历
        int arr[] = {(andMerge(qstrings, fields),0)...};//args的个数决定了func(int number)函数调用次数，也决定了数组开辟多少空间，数组中存放的值则是 参数
         QRegExp rx = QRegExp(" and", Qt::CaseInsensitive);
        if (fields.contains(rx)){
            fields = fields.remove(rx.pos(0), rx.cap(0).size());
        }

        QString result = QString(" WHERE %1").arg(fields);
        return result;
    }

    template <typename ...Args>
    static QString updateGerner(QString tableName, Args... qstrings)
    {
        QString fields;
        //实现func(int number)函数对 args 的遍历
        int arr[] = {(commaMerge(qstrings, fields),0)...};//args的个数决定了func(int number)函数调用次数，也决定了数组开辟多少空间，数组中存放的值则是 参数
        fields = fields.mid(1);

        QString result = QString("UPDATE %1 SET %2").arg(tableName).arg(fields);

        return result;
    }

    static QString deleteGener(QString tableName){
        return QString("DELETE FROM %1").arg(tableName);
    }

    template <typename ...Args>
    static QString insertGernerDirect(QString tableName, Args... qstrings)
    {
        QString fields;
        //实现func(int number)函数对 args 的遍历
        int arr[] = {(commaMerge(qstrings, fields),0)...};//args的个数决定了func(int number)函数调用次数，也决定了数组开辟多少空间，数组中存放的值则是 参数
        fields = "(" + fields.mid(1) + ")";


        QString result = QString("INSERT INTO %1 VALUES %2").arg(tableName).arg(fields);

        return result;
    }

    static QString insertGernerWithField(QString tableName, QStringList fieldList, QStringList valuesList)
    {
        QString fields;
        for(auto field:fieldList){
            fields += "," + field;
        }
        fields = "(" + fields.mid(1) + ")";

        QString values;
        for(auto value:valuesList){
            values += "," + value;
        }
        values = "(" + values.mid(1) + ")";

        QString result = QString("INSERT INTO %1 %2 VALUES %3").arg(tableName).arg(fields).arg(values);

        return result;
    }

    /************************************/

private:
    SqlGenerator(){}

};


//static SqlGenerator * m_sSqlGenerator = nullptr;

//SqlGenerator * SqlGenerator::getInstance(){
//    if(m_sSqlGenerator = nullptr){
//        m_sSqlGenerator = new SqlGenerator();
//        return m_sSqlGenerator;
//    }
//    else {
//        return m_sSqlGenerator;
//    }
//}





#endif // SQLGENERATOR_H


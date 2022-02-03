#include "mystudent.h"
#include <QMetaProperty>
#include <QtDebug>
#include <QMetaEnum>
MyStudent::MyStudent(QObject *parent) : QObject(parent)
{

}


QString MyStudent::getId() const
{
    return m_id;
}
void MyStudent::setId(const QString &id)
{
    m_id = id;
}

QString MyStudent::getName() const
{
    return m_name;
}
void MyStudent::setName(const QString &name)
{
    m_name = name;
}

//这里要记着必须这样写
MyStudent::Sex MyStudent::getSex() const
{
    return  m_sex;
}
QString MyStudent::getSexString() const
{
#if 0
    //这种方式只返回m_sex的数字下标
    return property("sex").toString();
#else

    QMetaEnum metaEnum = QMetaEnum::fromType<MyStudent::Sex>();
    QString str = metaEnum.valueToKey(m_sex);
    return str;

#endif
}
void MyStudent::setSex(const Sex &sex)
{
    m_sex = sex;
}

void MyStudent::setSex(const QString &sex)
{
    //首先获取元对象指针
    static const QMetaObject *meta = metaObject();

    //Returns the number of properties in this class, including the number of properties provided by each base class
    //获取该类所有的属性值
    QStringList properties;
    for(int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
        properties << QString::fromLatin1(meta->property(i).name());

    qDebug()<<properties;
    //这里输出结果：("id", "name", "sex")


    //根据属性名Sex查找m_sex属性对象QMetaProperty
    //发现属性名并返回其索引;否则返回-1。根据属性名"sex"查找该属性的索引
    static int propindex = meta->indexOfProperty("sex");


    //Returns the meta-data for the property with the given index. If no such property exists, a null QMetaProperty is returned.
    //返回与给定属性的元数据索引。如果没有这样的属性存在,返回一个null QMetaProperty。
    static const QMetaProperty mp = meta->property(propindex);

    //Returns the enumerator if this property's type is an enumerator type; otherwise the returned value is undefined.
    //返回枚举器如果这个属性的类型是一个枚举器类型;否则返回的值是未定义的。
    QMetaEnum menum = mp.enumerator();

    //把传入的sex转换成const char *
    const char *ntyp = sex.toStdString().c_str();

    //Returns the integer value of the given enumeration key, or -1 if key is not defined.
    //返回给定的枚举的整数值键,或-1如果没有定义的关键。
    m_sex = static_cast<Sex>(menum.keyToValue(ntyp));
    qDebug()<<"QMetaEnum"<<m_sex<<menum.name()<<menum.key(m_sex)<<menum.valueToKey(Sex::Man);

}
















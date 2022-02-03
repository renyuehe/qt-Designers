#ifndef MYSTUDENT_H
#define MYSTUDENT_H

#include <QObject>

/*
 * 学生类
 * 该类继承QObject，并且Q_OBJECT宏被包含在私有段中，以便moc生成可支持属性系统的C++代码
*/
class MyStudent : public QObject
{
    Q_OBJECT

public:
    //id代表属性m_id的名称，类型为QString（）
    //推荐属性使用“m_属性名称”的形式
    //WRITE函数使用“set属性名称”的形式
    //其中，属性名称、属性类型和获取属性的READ函数是必须提供的参数。其他项是可选的

    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(Sex sex READ getSex WRITE setSex)

    //用来生成字符串到枚举值的转换函数


    enum Sex {
        Man,
        Woman
    };
    Q_ENUM(Sex)
    explicit MyStudent(QObject *parent = nullptr);


    QString getId() const;
    void setId(const QString &id);

    QString getName() const;
    void setName(const QString &name);

    Sex getSex() const;
    QString getSexString() const;
    void setSex(const Sex &sex);
    void setSex(const QString &sex);


signals:

public slots:

private:
    QString m_id;
    QString m_name;
    Sex m_sex;
};

#endif // MYSTUDENT_H
























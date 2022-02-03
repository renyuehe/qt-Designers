#include <QApplication>
#include <QVariant>
#include <QtDebug>
#include "mystudent.h"

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);

    MyStudent student;
    student.setId("1");
    student.setName("Tom");
    student.setSex(MyStudent::Man);

    Q_ASSERT(student.getSex() == MyStudent::Man);

    //通过属性名称获取属性值
    QVariant v = student.property("id");
    QString str = v.toString();
    //qDebug()<<"ID="<<str;
    Q_ASSERT("1" == str);

    //通过属性名称设置属性值
    student.setProperty("id" , QVariant("2"));
    Q_ASSERT("2" == student.getId());
    //qDebug()<<"ID="<<student.getId();


    //直接调用设置性别函数
    student.setSex("Woman");

    qDebug()<<"Sex="<<student.getSex()<<student.getSexString();
    Q_ASSERT(student.getSex() == MyStudent::Woman);

    return 0;
}

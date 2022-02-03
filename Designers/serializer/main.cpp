#include <QApplication>
#include <QDataStream>
#include <QByteArray>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QVariant>
#include <QDebug>
#include <cstdarg>

struct MyData
{
    QString str;
    QPoint pt;
    int a;
    QVector<int> vec;

public:
    void show(){
        qDebug() << "a=" << a;
    }

public:
    // 重载序列化
    friend QDataStream & operator<<(QDataStream& stream, const MyData& data){
        stream << data.str;
        stream << data.pt;
        stream << data.a;
        stream << data.vec;
        return stream;
    }
    // 重载反序列化
    friend QDataStream & operator>>(QDataStream& stream, MyData& data) {
        stream >> data.str;
        stream >> data.pt;
        stream >> data.a;
        stream >> data.vec;
        return stream;
    }
};


struct MyData2
{
    MyData d;
public:
    void show(){
        qDebug() << "d.a=" << d.a;
    }
public:
    // 重载序列化
    friend QDataStream & operator<<(QDataStream& stream, const MyData2& data){
        stream << data.d;
        return stream;
    }
    // 重载反序列化
    friend QDataStream & operator>>(QDataStream& stream, MyData2& data) {
        stream >> data.d;
        return stream;
    }

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyData2 data;
    data.d.str = QStringLiteral(" chinese ");
    data.d.pt.setX(8);
    data.d.pt.setY(8);
    data.show();

    QByteArray ba;

    /*
    * serialize
    */
    QDataStream out(&ba, QIODevice::ReadWrite);
    out << data;

    /*
    * deserialize
    */
    QDataStream in(&ba, QIODevice::ReadOnly);
    MyData2 data2;
    while (!in.atEnd()) {
        in >> data2;
    }

    data2.show();

    return a.exec();
}

#include "Animal.h"
#include "Person.h"

#include <QDebug>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int a = 9;
    int b = 8;
    int c = a + b;

    int type = QMetaType::type("Person*");
    const QMetaObject *metaObj = QMetaType::metaObjectForType(type);


    QObject* obj = metaObj->newInstance();								//是产生新实例，并非单例。QT的插件dll产生的是单例：QPluginLoader pluginLoader(pluginPath + toolName + ".dll");QObject* tool = pluginLoader.instance();
    Animal* an = qobject_cast<Animal*>(obj);
//    an->setName("Hello");
    QMetaObject::invokeMethod(an, "setName", Qt::DirectConnection, Q_ARG(QString, "Hello"));
    qDebug() << an->name();

    QObject* obj2 = metaObj->newInstance();
    Animal* an2 = qobject_cast<Animal*>(obj2);
    QMetaObject::invokeMethod(an2, "setName", Qt::DirectConnection, Q_ARG(QString, "中文"));
//    an2->setName("nnn");
    qDebug() << an2->name();

    return app.exec();
}

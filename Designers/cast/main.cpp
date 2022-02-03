#include <QCoreApplication>
#include <QDebug>
#include <QObject>

#if 1

class base{
public:
    ~base(){}
    void baseFunc(){
        qDebug() << __LINE__ << "baseFunc";
    }
};

class Plugin : public QObject, public base
{
public:
    Plugin(QObject *parent=nullptr):QObject(parent){}
    ~Plugin(){}
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //! [1]
    QObject * pObject = new Plugin;
//        base * pBase = static_cast<base *>(pObject);//无法转换无关类
    Plugin * pPlugin = static_cast<Plugin *>(pObject);//父子可转
    pPlugin->baseFunc();

//    //! [2]
//    base * pBase = new Plugin;
//    Plugin * pB = static_cast<Plugin *>(pBase);//父子可转
//    pB->baseFunc();

    return a.exec();
}

#elif 0

/********************************** base ****************************************/
class base{
public:
    ~base(){}
    void baseFunc(){
        qDebug() << __LINE__ << "baseFunc";
    }
};

QT_BEGIN_NAMESPACE

#define base_IID "org.qt-project.Qt.base/1.0"
//此宏用于把标识符与类名接口关联起来。这个标识符是唯一的
//功能一:有此宏 就可以用qobject_cast转换了,如果不声明此宏则报错error: 'qt_metacall' is not a member of 'base'
Q_DECLARE_INTERFACE(base, base_IID)

QT_END_NAMESPACE

/********************************** Plugin ****************************************/

class Plugin : public QObject, public base
{
public:
    Plugin(QObject *parent=nullptr):QObject(parent){}
    ~Plugin(){}
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject * pObject = new Plugin;


    //! [2]
    base * pBase = qobject_cast<base *>(pObject);//qobject_cast()函数和标准C++的dynamic_cast()功能类似，只是其不需要RTTI的支持，而且可以跨越动态连接库的边界。 有两个限制：1# T类型必须继承自QObject。2# 在声明时必须有Q_OBJECT宏。
    pBase->baseFunc();

    return a.exec();
}


#else

class base{
public:
    ~base(){}
    void baseFunc(){
        qDebug() << __LINE__ << "baseFunc" << number;
    }

    int number = 10;
};

class Plugin : public QObject, public base
{
public:
    Plugin(QObject *parent=nullptr):QObject(parent){}
    ~Plugin(){}
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject * pObject = new Plugin;

    //! [3]
    base * pBase = dynamic_cast<base *>(pObject);//dymanic 可以转换无关类
    pBase->baseFunc();

    return a.exec();
}


#endif

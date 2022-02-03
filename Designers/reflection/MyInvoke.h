#ifndef MYINVOKE_H
#define MYINVOKE_H
#include <QWidget>
#include <QDebug>

class MyInvoke : public QWidget
{
    Q_OBJECT
public:
    explicit MyInvoke(){}
    ~MyInvoke(){}
    void fun1(QString funname){
        int  num = 10;
        bool returnValue = false;
        bool res = true;
        res = QMetaObject::invokeMethod(this,
                                        funname.toStdString().c_str(),
                                        Qt::DirectConnection,
                                        Q_RETURN_ARG(bool, returnValue),
                                        Q_ARG(int, num));

        if(!res)
        {
            qDebug() << "invoke fail.";
        }else{
            qDebug() << "invoke succed." << returnValue;
        }
    }
protected:
    Q_INVOKABLE bool MyInvokeTest1(int num){
        qDebug() << "hello invoke1." << num;
        return 1;
    }

    Q_INVOKABLE bool MyInvokeTest2(int num){
        qDebug() << "hello invoke2." << num*num;
        return 1;
    }
};
#endif // MYINVOKE_H

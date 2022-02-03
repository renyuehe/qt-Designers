#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>

namespace Ui {
class Widget;
}

const QEvent::Type NewType = (QEvent::Type)5001;//建议用5000以上唯一的标识

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void customEvent(QEvent *event);

private:
    Ui::Widget *ui;

    void Delay(unsigned int msec);

};

#endif // WIDGET_H

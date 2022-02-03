#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QResizeEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTimer::singleShot(2000, this, SLOT(createNewEvent()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createNewEvent()
{
    QResizeEvent re(QSize(1000, 600), QSize(this->width(), this->height()));

    qApp->sendEvent(this, &re);
}

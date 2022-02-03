#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initWidgetProperty();
    initConnect();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidgetProperty()
{
    this->setWindowTitle(tr("Mask Tool"));
    /* remove window border */
    this->setWindowFlags(Qt::FramelessWindowHint);
    /* set background transparent complete */
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void Widget::initConnect()
{
    connect(ui->m_frame, &MyFrame::windowChanged, this, &Widget::updateWidgetPosition);
}

void Widget::updateWidgetPosition(QPoint &point)
{
    this->move(pos().x() + point.x(), pos().y() + point.y());
}


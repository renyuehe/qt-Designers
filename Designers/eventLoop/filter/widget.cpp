#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_user->setText(QString("lee"));
    focusNextChild();
    ui->lineEdit_password->setText(QString("*******"));

//    QTimer::singleShot(2000, this, SLOT(callBack()));

#if 1
    ui->lineEdit_user->installEventFilter(this);
    ui->lineEdit_password->installEventFilter(this);
    ui->button_accept->installEventFilter(this);
    ui->button_cancel->installEventFilter(this);
#endif
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit_user || watched == ui->lineEdit_password
        || watched == ui->button_accept || watched == ui->button_cancel)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *e = static_cast<QKeyEvent *>(event);
            if(e->key() == Qt::Key_Space)
            {
                focusNextChild();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::callBack()
{
//    while(1);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_cancel_clicked()
{
    qApp->quit();
}

#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

/*!
 * \brief Widget::Widget 事件过滤器
 * 不借助Tab键的情况下使用Space键实现控件跳转
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_user->setText(QString("lee"));
    focusNextChild();
    ui->lineEdit_password->setText(QString("*******"));

    //监听控件
    ui->lineEdit_user->installEventFilter(this);
    ui->lineEdit_password->installEventFilter(this);
    ui->button_accept->installEventFilter(this);
    ui->button_cancel->installEventFilter(this);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    //定义事件处理动作
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

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_cancel_clicked()
{
    qApp->quit();
}

#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QEvent>

/*!
 * \brief Widget::Widget 使用sendEvent同步分发事件
 * 使用QPushButton模拟键盘的回删和向前删除按键
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_back_clicked()
{
    int key = Qt::Key_Backspace;

    QKeyEvent EventPress(QEvent::KeyPress, key, Qt::NoModifier);
    QApplication::sendEvent(ui->textEdit, &EventPress);

    QKeyEvent EventRelease(QEvent::KeyRelease, key, Qt::NoModifier);
    QApplication::sendEvent(ui->textEdit, &EventRelease);
}

void Widget::on_button_delete_clicked()
{
    int  key = Qt::Key_Delete;

    QKeyEvent EventPress(QEvent::KeyPress, key, Qt::NoModifier);
    QApplication::sendEvent(ui->textEdit, &EventPress);

    QKeyEvent EventRelease(QEvent::KeyRelease, key, Qt::NoModifier);
    QApplication::sendEvent(ui->textEdit, &EventRelease);
}

#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QEvent>

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

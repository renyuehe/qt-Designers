#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::NonModal);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "dialog mouse event!";
    }

    return QDialog::event(event);
}

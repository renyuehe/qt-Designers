#include "myframe.h"

MyFrame::MyFrame()
{

}

MyFrame::MyFrame(QWidget *parent, Qt::WindowFlags f)
{
    this->setParent(parent);
    this->setWindowFlags(f);
}

void MyFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        this->mouse_point = event->globalPosition().toPoint();
    }
}

void MyFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint new_mouse_point = event->globalPosition().toPoint();
        QPoint offset = new_mouse_point - mouse_point;
        mouse_point = new_mouse_point;
        emit windowChanged(offset);
    }
}

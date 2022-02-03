#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QPointF>


class MyFrame : public QFrame
{
    Q_OBJECT
public:
    MyFrame();
    explicit MyFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
signals:
    void windowChanged(QPoint& point);
private:
    QPoint mouse_point;
};

#endif // MYFRAME_H

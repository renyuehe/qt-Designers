/****************************************************************
 Doc    :   mygraphicsview.h
 Author :   BingLee
 Date   :   2020-9-25
 Info   :   QGraphicsView auto fit.
 https://blog.csdn.net/Bing_Lee (C)All rights reserved.
******************************************************************/

#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class QMouseEvent;
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicView(QGraphicsScene *scene);

public slots:
    void slot_zoomIn();//  { scale(1.2, 1.2); }
    void slot_zoomOut();// { scale(1/1.2, 1/1.2); }
    void slot_rotateLeft();// { rotate(-30); }
    void slot_rotateRight();// { rotate(30); }
    void slot_reset();

protected:
    virtual void mousePressEvent(QMouseEvent *event);

private:
    MyGraphicView* m_view;
};

#endif // MYGRAPHICVIEW_H

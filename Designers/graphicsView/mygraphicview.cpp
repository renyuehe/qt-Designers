#include "mygraphicview.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMenu>

MyGraphicView::MyGraphicView(QGraphicsScene *scene)
    :QGraphicsView(scene),
      m_view(this)
{
}


void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::RightButton)
    {
        QMenu *mouseLeftMenu = new QMenu(this);
        QAction* rotateLeft = new QAction(tr("rotateLeft"), this);
        QAction* rotateRight = new QAction(tr("rotateRight"), this);
        QAction* zoomIn = new QAction(tr("zoomIn"), this);
        QAction* zoomOut = new QAction(tr("zoomOut"), this);
        QAction* zoomReset = new QAction(tr("zoomReset"), this);

        mouseLeftMenu->addAction(rotateLeft);
        mouseLeftMenu->addAction(rotateRight);
        mouseLeftMenu->addAction(zoomIn);
        mouseLeftMenu->addAction(zoomOut);
        mouseLeftMenu->addAction(zoomReset);

        mouseLeftMenu->move(cursor().pos());
        mouseLeftMenu->show();

        connect(rotateLeft, SIGNAL(triggered()), this, SLOT(slot_rotateLeft()));
        connect(rotateRight, SIGNAL(triggered()), this, SLOT(slot_rotateRight()));
        connect(zoomIn, SIGNAL(triggered()), this, SLOT(slot_zoomIn()));
        connect(zoomOut, SIGNAL(triggered()), this, SLOT(slot_zoomOut()));
        connect(zoomReset, SIGNAL(triggered()), this, SLOT(slot_reset()));
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void MyGraphicView::slot_zoomIn()
{
    m_view->scale(1.2, 1.2);
}
void MyGraphicView::slot_zoomOut()
{
    m_view->scale(1/1.2, 1/1.2);
}
void MyGraphicView::slot_rotateLeft()
{
    m_view->rotate(-30);
}
void MyGraphicView::slot_rotateRight()
{
    m_view->rotate(30);
}
void MyGraphicView::slot_reset()
{
    QRectF rectItem = scene()->itemsBoundingRect();
    QRectF rectView = m_view->rect();
    qreal ratioView = rectView.height() / rectView.width();
    qreal ratioItem = rectItem.height() / rectItem.width();
    if (ratioView > ratioItem)
    {
        rectItem.moveTop(rectItem.width()*ratioView - rectItem.height());
        rectItem.setHeight(rectItem.width()*ratioView);

        rectItem.setWidth(rectItem.width() * 1.2);
        rectItem.setHeight(rectItem.height() * 1.2);
    }
    else
    {
        rectItem.moveLeft(rectItem.height()/ratioView - rectItem.width());
        rectItem.setWidth(rectItem.height()/ratioView);

        rectItem.setWidth(rectItem.width() * 1.2);
        rectItem.setHeight(rectItem.height() * 1.2);
    }

    m_view->fitInView(rectItem, Qt::KeepAspectRatio);
}

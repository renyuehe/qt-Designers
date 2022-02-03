#include "mainwindow.h"
#include "mygraphicview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMenu>

#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_vBoxLayout = new QVBoxLayout();
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    m_centralWidget->setLayout(m_vBoxLayout);

    DrawDemo();
    this->setWindowTitle("Demo1");
}

MainWindow::~ MainWindow()
{
}

void MainWindow::DrawDemo()
{
    QGraphicsScene *scene = new QGraphicsScene();   // 定义一个场景，设置背景色为白色
    scene->setBackgroundBrush(Qt::white);

    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    pen.setColor(QColor(0, 160, 230));
    pen.setWidth(1);

    QGraphicsRectItem *rectItem = new QGraphicsRectItem();   // 定义一个矩形图元
    rectItem->setRect(0, 0, 80, 80);
    rectItem->setPen(pen);
//    m_rectItem->setBrush(QBrush(QColor(255, 0, 255)));
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsLineItem *lineItem = new QGraphicsLineItem();    // 定义一个直线图元
    lineItem->setLine(QLineF(0, 0, 100, 100));
    pen.setColor(QColor(0, 50, 230));
    lineItem->setPen(pen);
    lineItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem();     //定义一个圆形图元
    pen.setColor(QColor(255, 0, 0));
    ellipseItem->setRect(QRectF(0,100,80,80));
    ellipseItem->setPen(pen);
//    ellipseItem->setBrush(QBrush(QColor(255, 0, 0)));
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsPathItem *pathItem = new QGraphicsPathItem();    // 定义一个路径图元
    QPainterPath path;
    path.moveTo(90, 50);
    path.lineTo(120, 50);
    path.lineTo(105, 10);
    path.closeSubpath();
    pathItem->setPath(path);
    pen.setColor(QColor(0, 160, 50));
    pathItem->setPen(pen);
    pathItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem();   // 定义一个多边形图元
    QPolygonF polygon;
    //add big Item. 2020-09-25
//    polygon << QPointF(-200.0, -400.0) << QPointF(200.0, -400.0)
//            << QPointF(400.0, 400.0) << QPointF(0.0, 400);
    //add small item. 2020-09-25
    polygon << QPointF(-20.0, -40.0) << QPointF(20.0, -40.0)
            << QPointF(40.0, 40.0) << QPointF(0.0, 40);
    polygonItem->setPolygon(polygon);
    pen.setColor(QColor(50, 120, 230));
    polygonItem->setPen(pen);
    polygonItem->setFlag(QGraphicsItem::ItemIsMovable);

//    scene->addItem(rectItem);      // 把矩形图元添加到场景
//    scene->addItem(lineItem);      // 把直线图元添加到场景
//    scene->addItem(pathItem);      // 把路径图元添加到场景
//    scene->addItem(ellipseItem);   // 把圆形图元添加到场景
    scene->addItem(polygonItem);   // 把多边形图元添加到场景

    m_view = new MyGraphicView(scene); // 定义一个视图，并把场景添加到视图
    m_view->setDragMode(QGraphicsView::RubberBandDrag); //设置view橡皮筋框选区域
    m_vBoxLayout->addWidget(m_view);
}





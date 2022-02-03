/****************************************************************
 Doc    :   mainwindow.h
 Author :   BingLee
 Date   :   2020-9-25
 Info   :   QGraphicsView auto fit.
 https://blog.csdn.net/Bing_Lee (C)All rights reserved.
******************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QVBoxLayout;
class MyGraphicView;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DrawDemo();

protected:

private:
    MyGraphicView *m_view;
    QGraphicsScene* m_scene;
    QVBoxLayout* m_vBoxLayout;
    QWidget* m_centralWidget;

signals:

public slots:

};

#endif // MAINWINDOW_H

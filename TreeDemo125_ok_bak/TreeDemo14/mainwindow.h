#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "define.h"


#include "MultilevelHeaderItem.h"
#include "MultilevelHeaderModel.h"
#include "MultilevelHeaderView.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;//////////////////////////////////////
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void initHeadDate(QList<HeaderItem> &listHeaderItem);//表头 位置还需考虑
    QStringList *getHeaderLabel(QList<HeaderItem> &listHeaderItem);//表头 位置还需考虑
private slots:
    void on_btn2_clicked(); //自定义model


    void on_ZoomInOut_clicked(bool checked);

    void on_Pushbutton_ZoomIn_clicked();

    void on_Pushbutton_zoomOut_clicked();

private:
    Ui::MainWindow *ui;
    QVector<CLASS*> mClasses;   //模拟数据


    QGraphicsScene *m_scene;//////////////////////////////////////

    ////////////////// 多级表头 //////////////////
    MultilevelHeaderView * m_pHHeaderview;
    MultilevelHeaderModel *m_pHHeaderModel;
    QVector<HeaderItem> heads;///表格头
    int modelColumnCount = 3;///设置模型字段
};



#endif // MAINWINDOW_H

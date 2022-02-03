#include "HYMdiArea.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HYMdiArea * mdw = new HYMdiArea(true);
    mdw->setAnimationTime(750,25);
    mdw->setAnimationCurveMode(QEasingCurve::Type::InOutBack);


    QHBoxLayout * layout = new QHBoxLayout;


    //控制窗口的设置
    {//控制窗口的设置
        QVBoxLayout * vlayout = new QVBoxLayout;
        QComboBox *combox = new QComboBox();
        combox->addItems(QStringList() << "tab" << "triTab" << "ellipse" << "cascade" << "tiled" << "center" << "8" << "random" << "horizental" << "vertical");
        QComboBox *combox2 = new QComboBox();
        combox2->addItems(QStringList() << "widget" << "pushbutton" << "calendary" << "tableWidget");

        QComboBox * combox3 = new QComboBox();
        combox3->addItems(QStringList() << "0,0" << "150,150" << "200, 400");


        QPushButton * btn = new QPushButton("add widget");
        vlayout->addWidget(combox);
        vlayout->addWidget(combox2);
        vlayout->addWidget(combox3);
        vlayout->addWidget(btn);

        QApplication::connect(combox, QOverload<const QString &>::of(&QComboBox::activated),[&](const QString &str){
            if(str == "tab"){
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::tabStateMode);
            }
            else if (str == "triTab") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::tabTriStateMode);
            }
            else if (str == "ellipse") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::ellipseStateMode);
            }
            else if (str == "cascade") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::cascadeStateMode);
            }
            else if (str == "tiled") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::tiledStateMode);
            }
            else if (str == "center") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::centeredStateMode);
            }
            else if (str == "8") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::figure8StateMode);
            }
            else if (str == "random") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::QrandomStateMode);
            }
            else if (str == "horizental") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::horizentalStateMode);
            }
            else if (str == "vertical") {
                mdw->setSubWindowViewMode(HMdiArea::SubWindowViewMode::verticalStateMode);
            }
        });

        QApplication::connect(combox2, QOverload<const QString &>::of(&QComboBox::activated), [&](const QString &str){
            if(str == "widget"){
                static int i = 0;
                QWidget *widget = new QWidget;
                mdw->addSubWindow(widget, "自定义名字 " + QString::number(i++))->show();
            }
            else if (str == "pushbutton") {
                static int i = 0;
                QPushButton *widget = new QPushButton;
                mdw->addSubWindow(widget, "自定义名字 " + QString::number(i++))->show();
            }
            else if (str == "calendary") {
                static int i = 0;
                QCalendarWidget *widget = new QCalendarWidget;
                mdw->addSubWindow(widget, "自定义名字 " + QString::number(i++))->show();
            }
            else if (str == "tableWidget") {
                static int i = 0;
                QTableWidget *widget = new QTableWidget;
                mdw->addSubWindow(widget, "自定义名字 " + QString::number(i++))->show();
            }
        });

        QApplication::connect(combox3, QOverload<const QString &>::of(&QComboBox::activated), [&](const QString &str){
            if(str == "0,0"){
                mdw->setSubWindowSize(QSize(0,0));
            }
            else if (str == "150,150") {
                mdw->setSubWindowSize(QSize(150,150));
            }
            else if (str == "200, 400") {
                mdw->setSubWindowSize(QSize(200,400));
            }
        });

        QApplication::connect(btn, &QPushButton::clicked,[&](){
            QWidget *widget = new QWidget;
            mdw->addSubWindow(widget, "btn")->show();
        });

        layout->addLayout(vlayout);
    }


    mdw->show();//多窗口显示

    QWidget w;
    w.setLayout(layout);
    w.setGeometry(0,0,200,100);
    w.show();//控制窗口显示

    return a.exec();
}

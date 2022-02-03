#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void initWidgetProperty();
    void initConnect();
public slots:
    void updateWidgetPosition(QPoint& point);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

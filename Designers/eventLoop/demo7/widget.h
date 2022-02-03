#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    bool event(QEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    Dialog *m_dialog;

};

#endif // WIDGET_H

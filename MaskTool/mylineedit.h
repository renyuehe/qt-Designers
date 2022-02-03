#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>
#include <QEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget* parent = nullptr);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
private:
    enum AnimationActiveType{Expand = 0, Narrow};
    void initPropertyAnimation(AnimationActiveType type);

private:
    QPropertyAnimation* m_animation;
    bool expand_state;
};

#endif // MYLINEEDIT_H

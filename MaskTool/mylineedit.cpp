#include "mylineedit.h"
#include "QRect"
#include <QCoreApplication>
#include <QTextCursor>
#include <QFocusEvent>
#include <QString>

MyLineEdit::MyLineEdit(QWidget *parent)
{
    setParent(parent);
    m_animation = new QPropertyAnimation(this, "geometry");
    expand_state = false;
}

void MyLineEdit::enterEvent(QEnterEvent *event)
{
    if (expand_state)
        return;
    if (m_animation->state() == QPropertyAnimation::Running)
        m_animation->stop();
    initPropertyAnimation(Expand);
    m_animation->start();
    expand_state = true;
}
#include <QDebug>
void MyLineEdit::leaveEvent(QEvent *event)
{
    if (hasFocus())
        return;
    if (m_animation->state() == QPropertyAnimation::Running)
        m_animation->stop();
    initPropertyAnimation(Narrow);
    m_animation->start();
    expand_state = false;
}

void MyLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event); //can't remove this,
    clear();
}

void MyLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    setText(QString("Mask"));
    this->setCursor(Qt::BlankCursor);
    if (m_animation->state() == QPropertyAnimation::Running)
        m_animation->stop();
    initPropertyAnimation(Narrow);
    m_animation->start();
    expand_state = false;
}

void MyLineEdit::initPropertyAnimation(AnimationActiveType type)
{
    QRect start, end;

    switch (type) {
        case Expand:
            m_animation->setDuration(150);
            start = QRect(300 - width()/2, height(), width(), height());
            end = QRect(100, height(), 400, height());
            m_animation->setEasingCurve(QEasingCurve::InQuad);
            break;
        case Narrow:
            m_animation->setDuration(150);
            start = QRect(300 - width()/2, height(), width(), height());
            end = QRect(200, height(), 200, height());
            m_animation->setEasingCurve(QEasingCurve::InQuad);
            break;
       default:
            QCoreApplication::instance()->exit(EXIT_FAILURE);
            break;
    }
    m_animation->setStartValue(start);
    m_animation->setEndValue(end);
}

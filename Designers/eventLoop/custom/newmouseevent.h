#ifndef MYEVENT_H
#define MYEVENT_H

#include <QEvent>
#include <QString>

class NewMouseEvent : public QEvent
{
public:
    explicit NewMouseEvent() :  QEvent(MouseTenClick) {}
    const static Type MouseTenClick = static_cast<Type>(QEvent::User+0x10);

};

#endif // MYEVENT_H

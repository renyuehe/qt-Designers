#ifndef HHTREEVIEW_H
#define HHTREEVIEW_H

#include <HTreeView.h>


//这里继承的,  目的是 冻结列 多级表头
class HHTreeView : public HTreeView
{
public:
    HHTreeView(QWidget *parent = Q_NULLPTR);
};

#endif // HHTREEVIEW_H

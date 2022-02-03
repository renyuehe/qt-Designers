#include "HVariantDelegate.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HVariantDelegate::HVariantDelegate(QObject * parent) :
    QStyledItemDelegate(parent)
{

}

HVariantDelegate::~HVariantDelegate()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QCalendarWidget>
#include <QPlainTextEdit>
#include <QLabel>
QWidget * HVariantDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    return new QWidget;
}

void HVariantDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
#if 0
    QStyledItemDelegate::paint(painter,option,index);

#else
    //绘制单元格边框
    /////////////////////////////////////////////////////////////////////
    painter->save();

    QRectF frameRect(option.rect.left() -  0.5, option.rect.top() - 0.5, option.rect.width(), option.rect.height());
//    QRectF frameRect(option.rect.left(), option.rect.top(), option.rect.width(), option.rect.height());

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::GlobalColor::gray);
    painter->setPen(pen);
    if (option.state & QStyle::State_Selected)///选中
    {
        painter->setBrush(option.palette.highlight());
    }
    else
    {
        if (index.data(Qt::BackgroundRole).isNull())
        {
            painter->setBrush(option.palette.base());
        }
        else
        {
            painter->setBrush(index.data(Qt::BackgroundRole).value<QColor>());
        }
    }
    painter->drawRect(frameRect);

    painter->restore();
    ////////////////////////////////////////////////////////////////////

    {
        QStyledItemDelegate::paint(painter,option,index);
    }

#endif
}

void HVariantDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStyledItemDelegate::setModelData(editor, model,index);
}


void HVariantDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void HVariantDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    {
        QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    }
}


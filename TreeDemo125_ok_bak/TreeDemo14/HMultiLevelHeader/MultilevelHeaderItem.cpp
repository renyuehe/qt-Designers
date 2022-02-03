#include "MultilevelHeaderItem.h"

#include <QDebug>
#define DebugInfo (qDebug() << __FILE__ << __LINE__)

MultilevelHeaderItem::MultilevelHeaderItem(MultilevelHeaderItem* parent):
   m_nRow(0),m_nColumn(0),m_pParentItem(parent)
{
}

MultilevelHeaderItem::MultilevelHeaderItem(int arow, int acolumn, MultilevelHeaderItem* parent):
    m_nRow(arow),m_nColumn(acolumn),m_pParentItem(parent)
{
}

MultilevelHeaderItem::~MultilevelHeaderItem()
{
}

MultilevelHeaderItem* MultilevelHeaderItem::insertChild(int row, int col)
{
    MultilevelHeaderItem* newChild = new MultilevelHeaderItem(row,col,this);
   m_hashChildrenItem.insert(QPair<int,int>(row,col),newChild);
    return newChild;
}

const MultilevelHeaderItem* MultilevelHeaderItem::child(int row,int col) const
{
    QHash<QPair<int,int>,MultilevelHeaderItem*>::const_iterator itr = m_hashChildrenItem.find(QPair<int,int>(row,col));
    if (itr != m_hashChildrenItem.end()) return itr.value();
    return 0;
}

MultilevelHeaderItem* MultilevelHeaderItem::child(int row,int col)
{
    QHash<QPair<int,int>,MultilevelHeaderItem*>::iterator itr = m_hashChildrenItem.find(QPair<int,int>(row,col));
    if (itr != m_hashChildrenItem.end()) return itr.value();
    return 0;
}

void MultilevelHeaderItem::setText(const QString& text)
{
    m_hashRoleData.insert(Qt::DisplayRole, text);
}

QVariant MultilevelHeaderItem::data(int role) const
{
    QHash<int,QVariant>::const_iterator itr = m_hashRoleData.find(role);
    if (itr != m_hashRoleData.end()) return itr.value();
    return QVariant();
}

void MultilevelHeaderItem::setData(const QVariant& data, int role)
{
    m_hashRoleData.insert(role,data);
}

void MultilevelHeaderItem::clear()
{
    QList<MultilevelHeaderItem*> items = m_hashChildrenItem.values();

    Q_FOREACH(MultilevelHeaderItem* item, m_hashChildrenItem)
    {
        if (item)
        {
            delete item;
        }
    }
     m_hashChildrenItem.clear();
}

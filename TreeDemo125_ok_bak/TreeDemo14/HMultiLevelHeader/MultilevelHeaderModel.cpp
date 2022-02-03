#include "MultilevelHeaderModel.h"

#include "MultilevelHeaderItem.h"

MultilevelHeaderModel::MultilevelHeaderModel(int rows, int cols, QObject* parent) :
QAbstractTableModel(parent),m_nRowCount(rows),m_nColumnCount(cols),m_pRootItem(new MultilevelHeaderItem())
{

}


/**
 * @brief MultilevelHeaderModel 无参构造
 * @param parent
 */
MultilevelHeaderModel::MultilevelHeaderModel(QObject *parent):
    QAbstractTableModel(parent),m_nRowCount(0),m_nColumnCount(0),m_pRootItem(new MultilevelHeaderItem())
{

}

MultilevelHeaderModel::~MultilevelHeaderModel()
{
    m_pRootItem->clear();
    delete m_pRootItem;
}


void MultilevelHeaderModel::SetModelData(const QList<HeaderItem> &listHeaderItem)
{

    //获取行列
    GetRowColCount(listHeaderItem, m_nRowCount, m_nColumnCount);

    //遍历合并单元格，设置设置背景色，文字
    for(int an = 0; an < listHeaderItem.size(); ++an)
    {
        const HeaderItem& tmpItem = listHeaderItem[an];

        //合并单元格
        if (tmpItem.nRowSpan > 1 || tmpItem.nColumnSpan > 1)
        {
            QModelIndex idx = index(tmpItem.nStartRow, tmpItem.nStartColumn);
            if (tmpItem.nRowSpan > 1)
            {
                setData(idx, tmpItem.nRowSpan, eRowSpanRole);
            }

            if (tmpItem.nColumnSpan > 1)
            {
                setData(idx, tmpItem.nColumnSpan, eColumnSpanRole);
            }
        }

        //设置文字和颜色
        setData(index(tmpItem.nStartRow,tmpItem.nStartColumn),tmpItem.bgColor,Qt::BackgroundRole);
        setData(index(tmpItem.nStartRow,tmpItem.nStartColumn),tmpItem.color,Qt::ForegroundRole);
        setData(index(tmpItem.nStartRow,tmpItem.nStartColumn),tmpItem.strContent,Qt::DisplayRole);
    }

    //表头显示青色
//    setData(index(0,0), QColor(Qt::cyan), Qt::BackgroundRole);

    beginResetModel();
    endResetModel();
}

QModelIndex MultilevelHeaderModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row,column,parent))
    {
        return QModelIndex();
    }

    MultilevelHeaderItem* parentItem;

    // parent item is always the root_item on table model
    if (!parent.isValid())
    {
       parentItem = m_pRootItem;
    }
    else
    {
        // no effect
        parentItem = static_cast<MultilevelHeaderItem*>(parent.internalPointer());
    }

    MultilevelHeaderItem* childItem = parentItem->child(row,column);
    if (!childItem)
    {
       childItem = parentItem->insertChild(row,column);
    }

    return createIndex(row,column,childItem);
}

QVariant MultilevelHeaderModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_nRowCount || index.row() < 0 || index.column() >= m_nColumnCount || index.column() < 0)
        return QVariant();

    MultilevelHeaderItem* item = static_cast<MultilevelHeaderItem*>(index.internalPointer());

    return item->data(role);
}

bool MultilevelHeaderModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid())
    {
         MultilevelHeaderItem* item = static_cast<MultilevelHeaderItem*>(index.internalPointer());
         if (role == eColumnSpanRole)
         {
             int col = index.column();
             int span = value.toInt();

             // span size should be more than 1, else nothing to do
             if (span > 0)
             {

                 // span size should be less than whole columns,
                 if (col + span - 1 >= m_nColumnCount)
                 {
                     span = m_nColumnCount - col;
                 }

                 item->setData(span, eColumnSpanRole);
             }
         }
         else if (role == eRowSpanRole)
         {
             int row = index.row();
             int span = value.toInt();

             // span size should be more than 1, else nothing to do
             if (span > 0)
             {
                 if (row+span-1 >= m_nRowCount)
                 {
                     span = m_nRowCount-row;
                 }

                 item->setData(span, eRowSpanRole);
             }
         }
         else
         {
             item->setData(value, role);

             emit dataChanged(index, index, {role});
         }

        return true;
    }

    return false;
}

Qt::ItemFlags MultilevelHeaderModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


/**
 * @brief CalculateRowColCount  根据表头信息计算行列总数
 * @param listHeaderItem    表头信息
 * @param nRowCount  输出 行计数
 * @param nColumnCount 输出 列计数
 */
void MultilevelHeaderModel::GetRowColCount(const QList<HeaderItem> &listHeaderItem, int &nRowCount, int &nColumnCount)
{
    nRowCount = 0;
    nColumnCount = 0;
    Q_FOREACH(const HeaderItem& tmpHeader, listHeaderItem)
    {
        if (tmpHeader.nStartRow + tmpHeader.nRowSpan > nRowCount)
        {
            nRowCount = tmpHeader.nStartRow + tmpHeader.nRowSpan;
        }
        if (tmpHeader.nStartColumn + tmpHeader.nColumnSpan > nColumnCount)
        {
            nColumnCount = tmpHeader.nStartColumn + tmpHeader.nColumnSpan;
        }
    }
}


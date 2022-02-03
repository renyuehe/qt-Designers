#include "Model.h"


/**** ItemModel ****/

ItemModel::ItemModel(QObject *parent):QAbstractItemModel (parent)
{

}

void ItemModel::setRoot(TreeItem *root)
{
    this->m_pRootItem = root;
}


QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        TreeItem * treeItem = static_cast<TreeItem*>(index.internalPointer());
        if (role == Qt::DisplayRole)
        {
            if(treeItem)
                return treeItem->m_vecItemData[index.column()].value(Qt::DisplayRole);

        }
        else if (role == Qt::EditRole) {
            if(treeItem)
                return treeItem->m_vecItemData[index.column()].value(Qt::EditRole);
        }

    }
    return QVariant();
}

int ItemModel::columnCount(const QModelIndex &parent) const
{

    //    TreeItem * treeItem = static_cast<TreeItem*>(parent.internalPointer());
    //    if(treeItem)
    //         return treeItem->m_vecChildrenItems.length();
    //    else
    //        return 0;

    return 3;
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    TreeItem * parentItem = nullptr;
    if(!parent.isValid())
        parentItem = this->m_pRootItem;
    else
        parentItem = static_cast<TreeItem* >(parent.internalPointer());

    return parentItem->childCount();


    /*********************************************/

//    if (parent.isValid() && parent.column() != 0)//相当其他节点
//    {
//        return 0;
//    }

//    TreeItem* pParentItem =nullptr;
//    if (parent.isValid())
//    {
//        //根据索引获取子节点地址
//        pParentItem = static_cast<TreeItem*>(parent.internalPointer());//有可能为空
//    }
//    else//无效index一定是根节点
//    {
//        pParentItem = m_pRootItem;
//    }

//    return pParentItem ? pParentItem->m_vecChildrenItems.length() : 0;
}

QModelIndex ItemModel::parent(const QModelIndex &index) const
{
    TreeItem * treeItem = nullptr;
    TreeItem * parentItem = nullptr;
    if(index.isValid())
        treeItem = static_cast<TreeItem*>(index.internalPointer());
    if(treeItem->m_pParentItem)
        parentItem = treeItem->m_pParentItem;

    if(parentItem)
    {
        if(parentItem == m_pRootItem)
        {
            return QModelIndex();
        }
        else
        {
            return createIndex(parentItem->m_vecChildrenItems.indexOf(treeItem), 0, parentItem);
        }
    }
    else {
        return QModelIndex();
    }
}

//成功返回一定是返回createindex,否则都返回ModelIndex
QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
    //  if (parent.isValid() && parent.column() != 0)
    //  {
    //      return 0;
    //  }

    TreeItem* pParentItem;
    if (parent.isValid())
    {
        //根据索引获取子节点地址
        pParentItem = static_cast<TreeItem*>(parent.internalPointer());//有可能为空
    }
    else {
        pParentItem = m_pRootItem;
    }


    if (!pParentItem)
    {
        return QModelIndex();
    }
    else
    {
        TreeItem* pChildItem = pParentItem->child(row);//第几个孩子节点

        if (pChildItem)
        {
            return createIndex(row, column, pChildItem);//核心,就是为了创建index
        }
        else
        {
            return QModelIndex();
        }
    }
}

/********************************************** abstract table model *************************************************/

TableModel::TableModel(QObject *parent):QAbstractTableModel (parent)
{

}

void TableModel::addRecord(QList<Cell> &rowRecord)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_table.appendRow(rowRecord);
    endInsertRows();
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return this->m_table.rowCount();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_table.columnCount();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        int column = index.column();
        int row = index.row();

        if(Qt::DisplayRole == role){
            return m_table.getCell(row, column).value(role);
        }
        else if (Qt::EditRole == role) {
            return m_table.getCell(row, column).value(role);
        }
    }
    return QVariant();
}

/********************************************** abstract list model *************************************************/


ListlModel::ListlModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ListlModel::addCell(const Cell &animal)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_animals << animal;
    endInsertRows();
}

int ListlModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_animals.count();
}

QVariant ListlModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_animals.count())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return m_animals[index.row()].value(Qt::DisplayRole);
    }
    return QVariant();
}

/********************************************** abstract list model *************************************************/

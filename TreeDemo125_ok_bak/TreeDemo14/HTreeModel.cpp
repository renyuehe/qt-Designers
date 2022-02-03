#include "HTreeItem.h"
#include "HTreeModel.h"
#include <QColor>
#include <QDateTime>
#include <QStringList>


TreeModel::TreeModel(QStringList headers,QObject *parent)
    : QAbstractItemModel(parent)
{
    mHeaders = headers;
    mRootItem = new HTreeItem;
}

TreeModel::~TreeModel()
{
    delete mRootItem;
}

HTreeItem *TreeModel::itemFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;

    HTreeItem *item = static_cast<HTreeItem*>(index.internalPointer());//返回 index void*
    return item;
}

HTreeItem *TreeModel::root()
{
    return mRootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    {//原 ok
        if (orientation == Qt::Horizontal)
        {
            if(role == Qt::DisplayRole)
            {
                return mHeaders.at(section);
            }
        }
        return QVariant();
    }


    {//天哥
//        if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        {
//            if (!m_pTreeNodeManager)
//            {
//                return QVariant();
//            }
//            else
//            {
//                return m_pTreeNodeManager->RootNode()->data(section, Qt::DisplayRole);
//            }
//        }
//        return QVariant("哈哈");
    }

}

#include <QLineEdit>
#include <QComboBox>
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    HTreeItem *item = static_cast<HTreeItem*>(index.internalPointer());//通过 item 取 index 对应的数据!!!!!!!!!!!!!
    if (role == Qt::DisplayRole)
    {
        return item->data(index.column());
    }
//    if (role == Qt::DecorationRole)
//    {
//        return QVariant("DeclarationRole");
//    }
    if (role == Qt::EditRole)
    {
        return QVariant("EditorRole");
    }
    else if (role == Qt::ToolTipRole)
    {
        return QVariant("tooltip");
    }
    else if (role == Qt::FontRole)//字体 大小 ？？ 斜体
    {
        return QVariant(QFont("楷体",static_cast<int>(10 * HGlobalZoom::getinstance()->getZoomScalePercent()),1,true));
    }
    else if( role == Qt::TextAlignmentRole )
    {
        if( index.column() == 0 )
        {
            //第1列左对齐
            return QVariant(Qt::AlignVCenter | Qt::AlignLeft);
        }
        else if( index.column() > 0 && index.column() < 6 )
        {
            //第2~6列右对齐
            return QVariant(Qt::AlignVCenter | Qt::AlignRight);
        }
        else
        {
            //其他列居中对齐
            return QVariant(Qt::AlignCenter);
        }
    }
    //    else if (role == Qt::BackgroundRole) {
    //        return QVariant(QColor("#FFFFFF"));
    //    }
    //    else if (role == Qt::ForegroundRole) {
    //        return QVariant(QColor("#0000FF"));
    //    }
    else if(role == Qt::TextColorRole)
    {
        if(index.column() == 6)
        {
            QString str = item->data(6).toString();
            if(str == QStringLiteral("不合格"))
            {
                //第7列（是否合格）如果不合格就设文本为红色
                return QVariant(QColor("#FF0000"));
            }
        }
        return QVariant();
    }
    else if (role == Qt::CheckStateRole)
    {
//        return QVariant(Qt::CheckState::Unchecked);
//        return QVariant(Qt::CheckState::PartiallyChecked);
//        return QVariant(Qt::CheckState::Checked);
    }
    else if (role == Qt::AccessibleTextRole)
    {
        //不清楚
    }
    else if (role == Qt::AccessibleDescriptionRole)
    {
        //不清楚
    }
    else if (role == Qt::SizeHintRole)//一个 单元格 影响一行
    {
        if(index.data(Qt::DisplayRole).toString() == "20")
        {
            return QSize(400, static_cast<int>(item->mRowHeight * HGlobalZoom::getinstance()->getZoomScalePercent()));//这里宽度不起作用,高度才起作用
        }
        else
        {
            return QSize(100,  static_cast<int>(item->mRowHeight * HGlobalZoom::getinstance()->getZoomScalePercent()));//这里宽度不起作用,高度才起作用
        }
    }
    return QVariant();
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;

//    return QAbstractItemModel::flags(index);
    return  Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsSelectable;
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();//有就直接返回

    HTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<HTreeItem*>(parent.internalPointer());

    HTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);//如果在 tree中存在,则创建 对应的 index
    else
        return QModelIndex();
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    HTreeItem *childItem = static_cast<HTreeItem*>(index.internalPointer());//index 的指向 void* 转换成 item
    HTreeItem *parentItem = childItem->parentItem();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    HTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<HTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}


int TreeModel::columnCount(const QModelIndex &parent) const
{
    return mHeaders.size();
}

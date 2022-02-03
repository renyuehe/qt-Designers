#ifndef MULTILEVELHEADERITEM_H
#define MULTILEVELHEADERITEM_H

#include <QModelIndex>
#include <QHash>
#include <QPair>

//表头数据枚举
enum eHeaderRole
{
    eColumnSpanRole = Qt::UserRole+1,
    eRowSpanRole,
    eColumnSizeRole,
    eRowSizeRole
};


/*多级表头类*/
class MultilevelHeaderItem
{
public:
    MultilevelHeaderItem(MultilevelHeaderItem* parent=0);
    MultilevelHeaderItem(int arow, int acolumn, MultilevelHeaderItem* parent=0);
    ~MultilevelHeaderItem();

private:

    // 行列属性
    int m_nRow;
    int m_nColumn;

    // 父节点
    MultilevelHeaderItem* m_pParentItem;

    //子节点
    QHash< QPair<int, int>, MultilevelHeaderItem*> m_hashChildrenItem;

    //节点数据
    QHash<int, QVariant> m_hashRoleData;

public:

    // interface
    MultilevelHeaderItem* insertChild(int row, int col);
    const MultilevelHeaderItem* child(int row,int col) const;
    MultilevelHeaderItem* child(int row,int col);
    void setData(const QVariant& data, int role);
    QVariant data(int role=Qt::UserRole+1) const;
    inline int column() const { return m_nColumn;}
    inline int row() const { return m_nRow;}
    MultilevelHeaderItem* parent() { return m_pParentItem;}
    void setText(const QString& text);
    void clear();
};

#endif // MULTILEVELHEADERITEM_H

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>

//单元格类
class Cell
{
public:
    Cell();
    Cell(const Cell &cell);
    Cell(int role, QVariant var);
    Cell(QList<int> & roleList, QList<QVariant> & valueList);
    Cell(QHash<int,QVariant> &cellValue);
    ~Cell(){}

    /*** 写操作 ***/
    void clear();
    //重新设置值
    void setValue(int role, QVariant var);
    void setValue(QHash<int,QVariant> &cellValue);
    bool setValue(QList<int> & roleList, QList<QVariant> & valueList);
    //有则不管,没有则添加
    void addValue(QHash<int,QVariant> &cellValue);
    void addValue(int,QVariant);
    //有则更新,没有跳过
    void updateValue(QHash<int,QVariant> &cellValue);
    void updateValue(int,QVariant);

    /*** 读操作 ***/
    const QVariant value(int role) const;
    const QHash<int, QVariant> getCellValue();

private:
    QHash<int,QVariant> cellValue;//单元格存储空间
};


class Table{
public:
    explicit Table(QList<QList<Cell>> m_llTable = QList<QList<Cell>>());
    ~Table();

    void appendRow(QList<Cell> row);

    int columnCount() const;
    int rowCount() const;
    const QList<Cell> & getRow(int row) const;

    const Cell getCell(int row, int column) const;

private:

    QList<QList<Cell>> m_llTable;
};



//类似于双向链表的数据结构类。存储节点信息，处理节点之间的关系
class TreeItem
{
public:
    explicit TreeItem(const QList<Cell>& vecData, TreeItem* pParent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* pChild);
    TreeItem* child(int number);
    int childCount() const;
    int columnCount() const;

public:
    //保存子对象地址
    QList<TreeItem*> m_vecChildrenItems;

    //存储当前节点的数据，有多少个数据就有多少列，此数据为一整行的数据
    QList<Cell> m_vecItemData;

    //保存父对象地址
    TreeItem* m_pParentItem;
};

#endif // TREEITEM_H

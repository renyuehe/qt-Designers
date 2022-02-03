#ifndef HTreeItem_H
#define HTreeItem_H

#include <QVariant>
#include <QVector>
#include <QList>
#include <QMap>

class HTreeItem
{
public:
    explicit HTreeItem(HTreeItem *parentItem = 0);
    ~HTreeItem();

    void appendChild(HTreeItem *child);      //在本节点下增加子节点
    void removeChilds();                    //清空所有节点

    HTreeItem *child(int row);               //获取第row个子节点指针
    QList<HTreeItem*> childList();
    HTreeItem *parentItem();                 //获取父节点指针
    int childCount() const;                 //子节点计数
    int row() const;                        //获取该节点是父节点的第几个子节点

    //核心函数：获取节点第column列的数据
    QVariant data(int column) const;

    //设置、获取节点是几级节点（就是树的层级）
    int level(){ return mLevel; }
    void setLevel(int level){ mLevel = level; }

    //设置、获取节点存的数据指针
    void setPtr(void* p){ mPtr = p; }
    void* ptr(){ return mPtr; }

    //保存该节点是其父节点的第几个子节点，查询优化所用
    void setRow(int row){
        mRow = row;
    }
	
private:
    QList<HTreeItem*> mChildItems;   //子节点
    HTreeItem *mParentItem;          //父节点
    int mLevel;     //该节点是第几级节点


    void* mPtr;     //存储数据的指针
    QVector<QMap<int, QVariant>> mRowData; //一行的数据

    int mRow;       //记录该item是第几个，可优化查询效率
public:
    int mRowHeight = 40; //行高,model中 data 函数的 Qt::sizeHintRole 来控制
    int mRowWidth = 100; //行高,model中 data 函数的 Qt::sizeHintRole 来控制

};

#endif

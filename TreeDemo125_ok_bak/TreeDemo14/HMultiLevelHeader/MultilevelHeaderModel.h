#ifndef MULTILEVELHEADERMODEL_H
#define MULTILEVELHEADERMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QColor>
#include <QFont>

#include "define.h"

class MultilevelHeaderItem;

class MultilevelHeaderModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    MultilevelHeaderModel(int rows, int cols, QObject* parent=0);

    /**
     * @brief MultilevelHeaderModel 无参构造
     * @param parent
     */
    explicit MultilevelHeaderModel(QObject* parent=nullptr);

    virtual ~MultilevelHeaderModel();

private:

    // properties
    //行列计数
    int m_nRowCount;
    int m_nColumnCount;


    // inherent features
    //表头数据根节点
    MultilevelHeaderItem* m_pRootItem;

public:

    /**
     * @brief SetModelData 设置表头数据
     * @param listHeaderItem 表头单元格数据
     */
    void SetModelData(const QList<HeaderItem>& listHeaderItem);


public:
    // override
    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const { Q_UNUSED(parent); return m_nRowCount; }
    virtual int columnCount(const QModelIndex &parent=QModelIndex()) const { Q_UNUSED(parent); return m_nColumnCount;}
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:

    /**
     * @brief CalculateRowColCount  根据表头信息计算行列总数
     * @param listHeaderItem    表头信息
     * @param nRowCount  输出 行计数
     * @param nColumnCount 输出 列计数
     */
    void GetRowColCount(const QList<HeaderItem>& listHeaderItem, int& nRowCount, int& nColumnCount);
    /**
     * @brief 设置默认的格子宽度
     */
    void setDefaltCellWidth();

    //////////////////////////////////////////////
public:
    //默认行列高(在哪设置? 初始化时候设置,   作用：与全局放大系数配合用)
    int m_defaltCellWidth = 200;
    int m_defaltCellHeight = 25;
    QFont m_defaltFont;//默认字体
};


#endif // MULTILEVELHEADERMODEL_H

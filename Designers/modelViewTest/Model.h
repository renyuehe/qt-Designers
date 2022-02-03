#ifndef MODEL_H
#define MODEL_H

#include <QDebug>
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QStringList>
#include <QHash>


#include "ModelCommon.h"

/********************************************** abstract item model *************************************************/

class ItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ItemModel(QObject *parent = Q_NULLPTR);
    virtual ~ItemModel(){}

    void setRoot(TreeItem * root);

    /****/
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    //保存数据根节点地址
    TreeItem* m_pRootItem;
};

/********************************************** abstract table model *************************************************/


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = Q_NULLPTR);

    void addRecord(QList<Cell> &rowRecord);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
//    QList<QList<Cell>> m_table;
    Table m_table;
};


/********************************************** abstract list model *************************************************/


class ListlModel : public QAbstractListModel
{
    Q_OBJECT
public:

    ListlModel(QObject *parent = 0);


    void addCell(const Cell &animal);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    QList<Cell> m_animals;
};


#endif // MODEL_H

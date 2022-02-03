#include "ModelCommon.h"



Cell::Cell()
{

}

Cell::Cell(const Cell &cell)
{
    this->cellValue = cell.cellValue;
}

Cell::Cell(int role, QVariant var)
{
    this->cellValue.insert(role, var);
}

Cell::Cell(QList<int> &roleList, QList<QVariant> &valueList)
{
    //传入参数list长度必须相等
    Q_ASSERT(roleList.length() == valueList.length());

    for(int i = 0; i< roleList.length(); ++i)
    {
        this->cellValue.insert(roleList.value(i), valueList.value(i));
    }
}

Cell::Cell(QHash<int, QVariant> &cellValue)
{
    this->cellValue = cellValue;
}

void Cell::clear()
{
    this->cellValue.clear();
}

void Cell::setValue(QHash<int, QVariant> &cellValue)
{
    this->cellValue = cellValue;
}


void Cell::setValue(int role, QVariant var)
{
    this->cellValue.find(role)->setValue(var);
}

bool Cell::setValue(QList<int> & roleList, QList<QVariant> & valueList)
{
    if(roleList.length() != valueList.length())
    {
        return false;
    }
    else
    {
        for(int i = 0; i< roleList.length(); ++i)
        {
            this->cellValue.insert(roleList.value(i), valueList.value(i));
        }
        return true;
    }
}

void Cell::addValue(QHash<int, QVariant> &cellValue)
{
    QHash<int, QVariant>::iterator iter = cellValue.begin();
    while(iter != cellValue.end())//遍历传入cellValue
    {
        auto this_iter = this->cellValue.find(iter.key());
        if(this_iter == this->cellValue.end())
        {
            this->cellValue.insert(iter.key(), iter.value());//如果没有找到对应的键值就加入新的
        }
    }
}

void Cell::addValue(int role, QVariant var)
{
    this->cellValue.insert(role, var);
}

void Cell::updateValue(QHash<int, QVariant> &cellValue)
{
    QHash<int, QVariant>::iterator iter = cellValue.begin();
    while(iter != cellValue.end())//遍历传入cellValue
    {
        auto this_iter = this->cellValue.find(iter.key());
        if(this_iter  != this->cellValue.end())
        {
            this_iter->setValue(iter.value()) ;//如果找到对应的键就update
        }
    }
}

void Cell::updateValue(int role, QVariant var)
{
    if(this->cellValue.find(role) != this->cellValue.end())
        this->cellValue.find(role).value().setValue(var);
}

const QVariant Cell::value(int role) const
{
    return cellValue.find(role).value();
}

const QHash<int, QVariant> Cell::getCellValue()
{
    return this->cellValue;
}

TreeItem::TreeItem(const QList<Cell> &vecData, TreeItem *pParent):
    m_vecItemData(vecData)
{
    m_pParentItem = pParent;//父子关联
    if (pParent)
        pParent->appendChild(this);//父子关联
}

void TreeItem::appendChild(TreeItem *pChild)
{
    if (pChild)
    {
        m_vecChildrenItems.append(pChild);
    }
}

TreeItem *TreeItem::child(int number)
{
    if(m_vecChildrenItems.length() > number)
        return m_vecChildrenItems.at(number);
    else
        return nullptr;
}

int TreeItem::childCount() const
{
    return m_vecChildrenItems.length();
}

int TreeItem::columnCount() const
{
    return  m_vecItemData.count();
}

Table::Table(QList<QList<Cell>> m_llTable)
{
    this->m_llTable = m_llTable;
}

Table::~Table()
{

}

void Table::appendRow(QList<Cell> row)
{
    this->m_llTable.append(row);
}

int Table::columnCount() const
{
    int columnCount = 0;
    for(auto iter : m_llTable)
    {
        int iterCount = iter.count();
        columnCount = columnCount > iterCount ? columnCount : iterCount;
    }
    return columnCount;
}

int Table::rowCount() const
{
    return this->m_llTable.count();
}

const QList<Cell> &Table::getRow(int row) const
{
    if(rowCount() > row)
    {
        return m_llTable[row];
    }
}

const Cell Table::getCell(int row, int column) const
{
    if(rowCount() > row)
    {
        m_llTable[row];
        auto rowData = getRow(row);
        if(rowData.count() > column)
            return rowData[column];
        else {
            return Cell();
        }
    }
    else {
        return Cell();
    }
}

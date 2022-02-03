#include "widget.h"
#include "ui_widget.h"
#include "ModelCommon.h"
#include "Model.h"
#include <QTreeView>
#include <QTableView>
#include <QListView>

/***************/

#include <QStandardItemModel>

/***************/


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /***********************************/
    ItemModel * itemModel = new ItemModel;

    QList<Cell> rowData;
    Cell cell(Qt::DisplayRole, QStringLiteral("显示"));

    rowData.push_back(cell);
    rowData.push_back(cell);
    rowData.push_back(cell);
    TreeItem * root = new TreeItem(rowData, nullptr);

    QList<Cell> rowData2;
    rowData2.push_back(cell);
    rowData2.push_back(cell);
    rowData2.push_back(cell);
    TreeItem * item = new TreeItem(rowData2, root);

    QList<Cell> row;
    row.push_back(cell);
    row.push_back(cell);
    row.push_back(cell);
    new TreeItem(row, root);

    QList<Cell> rowData3;
    rowData3.push_back(cell);
    rowData3.push_back(cell);
    rowData3.push_back(cell);
    TreeItem * item2 = new TreeItem(rowData3, item);

    cell.setValue(Qt::DisplayRole, QStringLiteral("猎鹰"));

    QList<Cell> rowData4;
    rowData4.push_back(cell);
    rowData4.push_back(cell);
    rowData4.push_back(cell);
    new TreeItem(rowData4, item2);

    itemModel->setRoot(root);
    QTreeView * treeView = new QTreeView();


    treeView->setModel(itemModel);
    treeView->show();

    /***********************************/


    TableModel * tableModel = new TableModel;

    QList<Cell> rowRecord;
    for (int i = 0; i < 3; ++i) {
        rowRecord.push_back(Cell(Qt::DisplayRole, "cell_DD"));
    }
    tableModel->addRecord(rowRecord);
    tableModel->addRecord(rowRecord);
    tableModel->addRecord(rowRecord);

    QTableView * tableView = new QTableView;
    tableView->setModel(tableModel);
    tableView->show();

    /***********************************/

    ListlModel *listModel = new ListlModel;

    listModel->addCell(Cell(Qt::DisplayRole, "wolf"));
    listModel->addCell(Cell(Qt::DisplayRole, "wolf2"));
    listModel->addCell(Cell(Qt::DisplayRole, "wolf555"));


    QListView * listView = new QListView();
    listView->setModel(listModel);
    listView->show();

}

Widget::~Widget()
{
    delete ui;
}

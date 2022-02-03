#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HTreeModel.h"

#include <QGraphicsRectItem>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    {
        //初始化模拟数据：学生成绩
        //10个班级、每个班级10000个学生，共10W行记录
        int nClass = 10;
        int nStudent = 100;
        for(int i=0;i<nClass;i++)
        {
            CLASS* c = new CLASS;
            c->name = QString("class%1").arg(i);
            for(int j=0;j<nStudent;j++)
            {
                STUDENT* s = new STUDENT;
                s->name = QString("name%1").arg(j);
                s->score1 = s->score2 = s->score3 = (j%10)*10;
                c->students.append(s);
            }
            mClasses.append(c);
        }
        ui->treeView->header()->setResizeContentsPrecision(3);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QStandardItemModel>//为多级表头服务
#include <QTableView>
#include <HVariantDelegate.h>

MultilevelHeaderView * m_pHHeaderview = nullptr;
MultilevelHeaderModel *m_pHHeaderModel = nullptr;
void MainWindow::on_btn2_clicked()
{
    //1，QTreeView常用设置项
//    ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);			//单元格不能编辑
    ui->treeView->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
    ui->treeView->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
//  ui->treeView t->setAlternatingRowColors(true);                       //每间隔一行颜色不一样，当有qss时该属性无效
    ui->treeView->setFocusPolicy(Qt::NoFocus);                         //去掉鼠标移到单元格上时的虚线框

    {
        //2，列头相关设置
        ui->treeView->header()->setHighlightSections(true);                //列头点击时字体变粗，去掉该效果
        ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);      //列头文字默认居中对齐
        ui->treeView->header()->setDefaultSectionSize(100);                //默认列宽100
        ui->treeView->header()->setStretchLastSection(true);               //最后一列自适应宽度
        ui->treeView->header()->setSortIndicator(0,Qt::AscendingOrder);    //按第1列升序排序
    }

    //3，构造Model
    QStringList headers;
    headers << QStringLiteral("班级/姓名")
            << QStringLiteral("语文")
            << QStringLiteral("数学")
            << QStringLiteral("外语")
            << QStringLiteral("总分")
            << QStringLiteral("平均分")
            << QStringLiteral("是否合格")
            << QStringLiteral("是否评优");
    //注意：此时构造的是自定义的TreeModel！
//    TreeModel* model = new TreeModel(headers,ui->treeView);

    TreeModel * model = new TreeModel(headers);

//    ui->treeView->setModel(model);

    HTreeItem* root = model->root();
    foreach (CLASS* c, mClasses)
    {
        //一级节点：班级
        HTreeItem* itemClass = new HTreeItem(root);
        itemClass->setLevel(1);     //设为一级节点，供显示时判断节点层级来转换数据指针类型
        itemClass->setPtr(c);       //保存CLASS* c为其数据指针，显示时从该CLASS*取内容显示
        root->appendChild(itemClass);

        foreach (STUDENT* s, c->students)
        {
            HTreeItem* itemStudent = new HTreeItem(itemClass);
            itemStudent->setLevel(2);   //设为一级节点，供显示时判断节点层级来转换数据指针类型
            itemStudent->setPtr(s);     //保存STUDENT* s为其数据指针，显示时从STUDENT*取内容显示
            itemClass->appendChild(itemStudent);
        }
    }


    //4，应用model
    ui->treeView->setModel(model);
    connect(ui->treeView, &HTreeView::zoomEvent, this, [=](bool isZoomIn){
        if(isZoomIn){
            on_Pushbutton_ZoomIn_clicked();
        }
        else {
            on_Pushbutton_zoomOut_clicked();
        }
    });
    ui->treeView->header()->setStretchLastSection(false);


    {//有问题, 如果直接使用多级表头会导致崩溃, 崩溃入口 setModel ui->treeView->setModel(HTreeModel);
        {
            //表头
            m_pHHeaderview = new MultilevelHeaderView;
            m_pHHeaderModel = new MultilevelHeaderModel;
            QList<HeaderItem> listHeaderItem;
            initHeadDate(listHeaderItem);
            m_pHHeaderModel->SetModelData(listHeaderItem);
            m_pHHeaderview->setHeaderModel(m_pHHeaderModel);
            ui->treeView->setHeader(m_pHHeaderview);

            ui->treeView->header()->setVisible(true);
        }
    }

    {
        HVariantDelegate * varDelegate = new HVariantDelegate;
        ui->treeView->setItemDelegate(varDelegate);
    }
}


void MainWindow::on_ZoomInOut_clicked(bool checked)
{
    if(checked){
//        ui->treeView->resize(100,400);
        static_cast<HTreeItem *>(ui->treeView->model()->index(0,0).internalPointer())->mRowHeight = 100;
        ui->treeView->doItemsLayout();
    }
    else {
        //ui->treeView->resize(400,400);
        static_cast<HTreeItem *>(ui->treeView->model()->index(0,0).internalPointer())->mRowHeight = 400;
        ui->treeView->doItemsLayout();
    }
}

static int headerWidth = 200;
static int headerHeight = 50;
#include <QtDebug>
void MainWindow::on_Pushbutton_ZoomIn_clicked()
{
    HGlobalZoom::getinstance()->zoomOutCustom(1.1);



//    ui->treeView->viewport()->update();//只更新了item 字体大小 没有更新行高
//    ui->treeView->header()->resizeSection(0, static_cast<int>(ui->treeView->header()->sectionSize(0) * 1.1));//更新 header 宽度(以及列宽)   //表头放大先不管, 研究了多级表头后再来管 //还没有做限制

//     ui->treeView->header()->resizeSection(0, static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));//更新 header 宽度  //表头放大先不管, 研究了多级表头后再来管 //还没有做限制

      m_pHHeaderview->zoomByScale(HGlobalZoom::getinstance()->getZoomScalePercent());

     {//影响的不是多级表头,而是被隐藏的原表头
//         ui->treeView->header()->setMinimumHeight(static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));
//         ui->treeView->header()->setMaximumHeight(static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));
     }


     ui->treeView->doItemsLayout();//更新 item 字体大小 和 行高度
}


void MainWindow::on_Pushbutton_zoomOut_clicked()
{
    HGlobalZoom::getinstance()->zoomInCustom(1.1);


//    ui->treeView->viewport()->update();//只更新了item 字体大小 没有更新行高
//    ui->treeView->header()->resizeSection(0, static_cast<int>(ui->treeView->header()->sectionSize(0) / 1.1));//更新 header 宽度  //表头放大先不管, 研究了多级表头后再来管 //还没有做限制

//    ui->treeView->header()->resizeSection(0, static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));//更新 header 宽度  //表头放大先不管, 研究了多级表头后再来管 //还没有做限制

    m_pHHeaderview->zoomByScale(HGlobalZoom::getinstance()->getZoomScalePercent());

    {
//        ui->treeView->header()->setMinimumHeight(static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));
//        ui->treeView->header()->setMaximumHeight(static_cast<int>(headerWidth * HGlobalZoom::getinstance()->getZoomScalePercent()));
    }

    ui->treeView->doItemsLayout();//更新 item 字体大小 和 行高度
}


////////////////

///初始化表格头数据
void MainWindow::initHeadDate(QList<HeaderItem>& listHeaderItem)
{
    listHeaderItem.clear();
    listHeaderItem << HeaderItem(QStringLiteral("名称"), 0, 0, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("描述"), 0, 1, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("备注"), 0, 2, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("名称"), 0, 3, 2, 1);
    listHeaderItem << HeaderItem(QStringLiteral("描述"), 0, 4, 1, 2);
    listHeaderItem << HeaderItem(QStringLiteral("备注"), 0, 5, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("名称"), 0, 6, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("描述"), 0, 7, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("备注"), 0, 8, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("名称"), 0, 9, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("描述"), 0, 10, 1, 1);
    listHeaderItem << HeaderItem(QStringLiteral("备注"), 0, 11, 1, 1);
}

QStringList *MainWindow::getHeaderLabel(QList<HeaderItem> &listHeaderItem)
{
    QStringList *strList = new QStringList;
    int columnMax = 0;
    for (int i = 0; i < listHeaderItem.length(); ++i) {
        HeaderItem item = listHeaderItem.at(i);
        int columnCount = item.nStartColumn+item.nColumnSpan - 1;
        columnMax = columnCount > columnMax ? columnCount : columnMax;
    }
    for (int i = 0; i <= columnMax; ++i) {
        *strList << "";
    }
    return strList;
}

///////////////


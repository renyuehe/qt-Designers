#include "HTreeView.h"
#include <QHeaderView>
HTreeView::HTreeView(QWidget *parent):
    QTreeView (parent)
{

}

#include <HTreeItem.h>
//绘制分支
void HTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    //继承
    {
        painter->save();
        QTreeView::drawBranches(painter, rect, index);
        painter->restore();
    }

    //绘制branch
    {
        HTreeItem * node = static_cast<HTreeItem *>(index.internalPointer());

//        bool hasChild = node->child().size() != 0;//是否有孩子
        bool hasChild = false;
        if(node->childCount()){
            hasChild = true;
        }
        else
        {
            hasChild = false;
        }

        QList<HTreeItem *> children = node->parentItem()->childList();
        bool has_next_siblings = children.indexOf(node) != (children.size() - 1);//是否有向后的兄弟
//        bool has_pre_siblings = children.indexOf(node) != 0;//是否有向前的兄弟

        int level = node->level();
        int indentaion = indentation();//缩进
        int indentaions = indentaion * (level - 1);//缩进距离

        QRect r = rect;
        r.setLeft(r.left() + indentaions);//图标绘制位置

        painter->save();
        QPen pen;
        pen.setStyle(Qt::PenStyle::DotLine);
        painter->setPen(pen);

        bool expaned = isExpanded(index);//节点是否展开

        QLine line(r.center() + QPoint(0, r.top() - r.center().y()), r.center() + QPoint(0, r.bottom() - r.center().y()));
        line.translate(-indentaion, 0);
        //QLine line(r.topLeft(), r.bottomLeft());
        //循环绘制(具有兄弟节点的)父节点向下的竖线
        HTreeItem * parent_node = node->parentItem();
        HTreeItem * sub_node = node;
//        bool isNeed = node->children().size() == 0;

        for (int i = level - 1; i >= 0; --i)
        {
            QList<HTreeItem *> children = parent_node->childList();
            bool has_next_siblings = children.indexOf(sub_node) != (children.size() - 1);//父节点是否有(向后的)兄弟

            if (has_next_siblings)
            {
                painter->drawLine(line);
            }


            if (level - 1 == i)
            {
                QPoint pos = (line.p1() + line.p2()) / 2;
                QPoint pos2 = pos + QPoint(indentaion / 2, 0);

                painter->drawLine(pos, pos2);

                if (!has_next_siblings)
                {
                    painter->drawLine(line.p1(), (line.p1() + line.p2()) / 2);
                }
            }

            sub_node = parent_node;
            parent_node = parent_node->parentItem();
            line.translate(-indentaion, 0);
        }

        QPixmap pix;
        if (expaned)
        {
            if (hasChild)
            {
                pix = QPixmap(":/branch-expand.png");
            }
        }
        else
        {
            if (hasChild)
            {
                pix = QPixmap(":/branch-collapse.png");
            }
        }
        if (pix.isNull() == false)
        {
            QRect pixRect = QRect(QPoint(0, 0), pix.size());
            pixRect.moveCenter(r.center());

            if (expaned)
            {
                QLine line(r.center(), r.center() + QPoint(0, r.bottom() - r.center().y()));
                painter->drawLine(line);
            }

            painter->drawPixmap(pixRect, pix);
        }

        painter->restore();
    }
}


void HTreeView::drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    QTreeView::drawRow(painter, options, index);

    {
//        //绘制网格线
//        QPen pen;
//        int m_iWidth = 2;
//        QColor color(Qt::GlobalColor::red);
//        pen.setWidth(m_iWidth);
//        pen.setColor(color);

//        painter->save();
//        painter->setPen(pen);
//        painter->drawRect(options.rect);
//        painter->restore();
    }
}

#include <QtDebug>
void HTreeView::wheelEvent(QWheelEvent *Event)
{
    if ((Event->modifiers() == Qt::ControlModifier) && (Event->delta() > 0))
    {
    //        dosomethine()
        emit(zoomEvent(true));//放大信号
        qDebug() << "zoom out";
    }
    else if ((Event->modifiers() == Qt::ControlModifier) && (Event->delta() < 0))
    {
    //        dosomethine()
            emit(zoomEvent(false));//缩小信号
            qDebug() << "zoom In";
    }
}

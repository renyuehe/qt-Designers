#include "MultilevelHeaderView.h"

#include "MultilevelHeaderItem.h"
#include "MultilevelHeaderModel.h"

#include <QPainter>
#include <QVariant>
#include <qmath.h>
#include <qdrawutil.h>
#include <QStandardItem>
#include <QMouseEvent>
#include <QWidget>

#include <QDebug>
#define DebugInfo (qDebug() << __FILE__ << __LINE__)

#include "define.h"

/**
 * @brief MultilevelHeaderView  多级表头构造函数
 * @param orientation   方向
 * @param parent    父窗口
 */
MultilevelHeaderView::MultilevelHeaderView(Qt::Orientation orientation, QWidget *parent):
    QHeaderView(orientation,parent),m_bAdjustLastSection(false)
{

    connect(this, SIGNAL(sectionResized(int, int, int)), this, SLOT(onSectionResized(int,int,int)));

}

MultilevelHeaderView::~MultilevelHeaderView()
{
}

/**
 * @brief ZoomToScale 缩放表头
 * @param fScale 比例值 大于1 放大， 小于1缩小
 */
void MultilevelHeaderView::ZoomToScale(double dScaleFactor, qreal dFontPointSize)
{
    MultilevelHeaderModel* pHeaderModel = qobject_cast<MultilevelHeaderModel*>(model());

    DebugInfo << "ZoomToScale" << pHeaderModel << this;

    int nRowCount = pHeaderModel->rowCount();
    int nColumnCount = pHeaderModel->columnCount();

    //设置数据
    for (int row = 0; row < nRowCount; ++row)
    {
        for (int col = 0; col < nColumnCount; ++col)
        {
            QSize newSize = pHeaderModel->index(row,col).data(Qt::SizeHintRole).toSize();


            if (row == 0 && col == 0)
            {
                DebugInfo << "HeaderCellSzie" << newSize;
            }

            newSize.setWidth(qCeil(newSize.width() * dScaleFactor));
            newSize.setHeight(qCeil(newSize.height() * dScaleFactor));
            pHeaderModel->setData(pHeaderModel->index(row,col), newSize,Qt::SizeHintRole);

            if (row == 0 && col == 0)
            {
                DebugInfo << "HeaderCellSzie after" << newSize;
            }
        }
    }

//    //调整行高和列宽
//    if (orientation() == Qt::Vertical)
//    {
//        for (int an = 0; an < nRowCount; ++an)
//        {
//            resizeSection(an, qCeil(sectionSize(an) * dScaleFactor));
//        }
//    }
//    else
//    {
//        for (int an = 0; an < nColumnCount; ++an)
//        {
//            resizeSection(an, qCeil(sectionSize(an) * dScaleFactor));
//        }
//    }

    QFont tmpFont = font();
    tmpFont.setPointSizeF(dFontPointSize);
    setFont(tmpFont);
}

void MultilevelHeaderView::zoomByScale(double scale)
{
    MultilevelHeaderModel* pHeaderModel = qobject_cast<MultilevelHeaderModel*>(model());//拿到 model

    DebugInfo << "zoomByScale" << pHeaderModel << this;

//    int nRowCount = pHeaderModel->rowCount();//行数
    int nColumnCount = pHeaderModel->columnCount();//列数

    {
        {//调整行高
         //好像没有直接调整行高的接口
        }

        {
            //调整列宽
            for (int an = 0; an < nColumnCount; ++an)
            {
                resizeSection(an, qCeil(pHeaderModel->m_defaltCellWidth * scale));

                setRowHeight(an, qCeil(pHeaderModel->m_defaltCellHeight * scale));
            }
        }

    }

    {
        QFont tmpFont = pHeaderModel->m_defaltFont;
        qreal size = tmpFont.pointSizeF();
        tmpFont.setPointSizeF(size * scale);
//        tmpFont.setPointSizeF();
        setFont(tmpFont);
    }
}

#if 0
//qheaderview_p.h
//#include <QtWidgets/qtw
void MultilevelHeaderView::resizeSection(int logical, int size)
{
    Q_D(QHeaderView);
    if (logical < 0 || logical >= count() || size < 0 || size > maxSizeSection)
        return;

    if (isSectionHidden(logical)) {
        d->hiddenSectionSize.insert(logical, size);
        return;
    }

    int visual = visualIndex(logical);
    if (visual == -1)
        return;

    if (d->state == QHeaderViewPrivate::ResizeSection && !d->cascadingResizing && logical != d->section)
        d->preventCursorChangeInSetOffset = true;

    int oldSize = d->headerSectionSize(visual);
    if (oldSize == size)
        return;

    d->executePostedLayout();
    d->invalidateCachedSizeHint();

    if (stretchLastSection() && logical == d->lastSectionLogicalIdx)
        d->lastSectionSize = size;

    d->createSectionItems(visual, visual, size, d->headerSectionResizeMode(visual));

    if (!updatesEnabled()) {
        if (d->hasAutoResizeSections())
            d->doDelayedResizeSections();
        emit sectionResized(logical, oldSize, size);
        return;
    }

    int w = d->viewport->width();
    int h = d->viewport->height();
    int pos = sectionViewportPosition(logical);
    QRect r;
    if (d->orientation == Qt::Horizontal)
        if (isRightToLeft())
            r.setRect(0, 0, pos + size, h);
        else
            r.setRect(pos, 0, w - pos, h);
    else
        r.setRect(0, pos, w, h - pos);

    if (d->hasAutoResizeSections()) {
        d->doDelayedResizeSections();
        r = d->viewport->rect();
    }

    // If the parent is a QAbstractScrollArea with QAbstractScrollArea::AdjustToContents
    // then we want to change the geometry on that widget. Not doing it at once can/will
    // cause scrollbars flicker as they would be shown at first but then removed.
    // In the same situation it will also allow shrinking the whole view when stretchLastSection is set
    // (It is default on QTreeViews - and it wouldn't shrink since the last stretch was made before the
    // viewport was resized)

    QAbstractScrollArea *parent = qobject_cast<QAbstractScrollArea *>(parentWidget());
    if (parent && parent->sizeAdjustPolicy() == QAbstractScrollArea::AdjustToContents)
        parent->updateGeometry();

    d->viewport->update(r.normalized());
    emit sectionResized(logical, oldSize, size);
}
#endif


/**
 * @brief setRowHeight 设置表头指定行行高
 * @param row 指定行
 * @param rowHeight 行高
 */
void MultilevelHeaderView::setRowHeight(int row, int rowHeight)
{
    MultilevelHeaderModel* md = qobject_cast<MultilevelHeaderModel*>(model());
    const int cols = md->columnCount();
    for (int col=0;col<cols;++col)
    {
        QSize sz = md->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setHeight(rowHeight);
        md->setData(md->index(row,col),sz,Qt::SizeHintRole);
    }
    if (orientation() == Qt::Vertical)
    {
        resizeSection(row,rowHeight);
    }
}


/**
 * @brief setColumnWidth 设置表头指定列宽
 * @param col 指定列
 * @param colWidth 列宽
 */
void MultilevelHeaderView::setColumnWidth(int col, int colWidth)
{
    MultilevelHeaderModel* md = qobject_cast<MultilevelHeaderModel*>(model());
    const int rows = md->rowCount();
    for (int row=0;row<rows;++row)
    {
        QSize sz = md->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setWidth(colWidth);
        md->setData(md->index(row,col),sz,Qt::SizeHintRole);
    }
    if (orientation() == Qt::Horizontal)
        resizeSection(col,colWidth);
}


void MultilevelHeaderView::setSpan(int row, int column, int rowSpanCount, int columnSpanCount)
{
    MultilevelHeaderModel* md = qobject_cast<MultilevelHeaderModel*>(model());
    QModelIndex idx = md->index(row,column);
    if (rowSpanCount > 1)
    {
        md->setData(idx,rowSpanCount,eRowSpanRole);
    }

    if (columnSpanCount > 1)
    {
        md->setData(idx,columnSpanCount,eColumnSpanRole);
    }
}

void MultilevelHeaderView::setCellBackgroundColor(const QModelIndex& index, const QColor& color)
{
    MultilevelHeaderModel* md = qobject_cast<MultilevelHeaderModel*>(model());
    md->setData(index,color,Qt::BackgroundRole);
}

void MultilevelHeaderView::setCellForegroundColor(const QModelIndex& index, const QColor& color)
{
    MultilevelHeaderModel* md = qobject_cast<MultilevelHeaderModel*>(model());
    md->setData(index,color,Qt::ForegroundRole);
}


/**
 * @brief slotResizeLastSection 重设最后一列的宽度，在tree收缩时加1，伸展时减1。实质上是想通过列的resize函数引起整个水平头的位置更新。
 * 不通过这样的处理，在tree的伸展收缩或者整个界面隐藏和展示时会水平头的位置不正确。
 */
void MultilevelHeaderView::slotResizeLastSection()
{
    int nCount = count();
    int nWidth = sectionSize(nCount - 1);

    if (m_bAdjustLastSection)
    {
        resizeSection(nCount - 1, nWidth + 1);
        resizeSection(nCount - 1, nWidth);
        m_bAdjustLastSection = false;
    }
    else
    {
        resizeSection(nCount - 1, nWidth - 1);
        resizeSection(nCount - 1, nWidth);
        m_bAdjustLastSection = true;
    }
}


/**
 * @brief setHeaderModel 设置模型函数，根据表头方向，调整尺寸
 * @param pModel 模型
 */
void MultilevelHeaderView::setHeaderModel(QAbstractItemModel *pModel)
{
    setModel(pModel);

    //设置默认大小
    {
        MultilevelHeaderModel* pMultiModel = qobject_cast<MultilevelHeaderModel*>(pModel);
        if (pMultiModel)
        {
            //其他地方用于放大 缩小, 这里用于初始化 表头 宽高
            zoomByScale(HGlobalZoom::getinstance()->getZoomScalePercent());
        }

    }
}


void MultilevelHeaderView::mousePressEvent(QMouseEvent* event)
{
    QHeaderView::mousePressEvent(event);
    QPoint pos = event->pos();
    QModelIndex index = indexAt(pos);
    const int nCurOrientation = orientation();

    if (index.isValid())
    {
        int beginSection = -1;
        int endSection   = -1;
        int numbers = 0;
        numbers = getSectionRange(index, &beginSection, &endSection);

        if (numbers > 0)
        {
            emit sectionPressed(beginSection,endSection);
            return;
        }
        else
        {
            const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
            const int nLevelCount = (nCurOrientation == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
            int logicalIdx = (nCurOrientation == Qt::Horizontal)?index.column():index.row();
            int curLevel   = (nCurOrientation == Qt::Horizontal)?index.row():index.column();
            for (int i=0;i<nLevelCount;++i)
            {
                QModelIndex cellIndex = (nCurOrientation == Qt::Horizontal)?tblModel->index(i,logicalIdx):tblModel->index(logicalIdx,i);
                numbers = getSectionRange(cellIndex,&beginSection,&endSection);
                if (numbers > 0)
                {
                    if (beginSection <= logicalIdx && logicalIdx <= endSection)
                    {
                        int beginLevel = (nCurOrientation == Qt::Horizontal)?cellIndex.row():cellIndex.column();
                        QVariant levelSpanCnt = cellIndex.data((nCurOrientation == Qt::Horizontal) ? eRowSpanRole:eColumnSpanRole);
                        if (!levelSpanCnt.isValid())
                            continue;
                        int endLevel   = beginLevel + levelSpanCnt.toInt()-1;
                        if (beginLevel <= curLevel && curLevel <= endLevel)
                        {

                            DebugInfo << QStringLiteral("计算涉及范围:") << beginSection << endSection;

                            emit sectionPressed(beginSection,endSection);
                            break;
                        }
                    }
                }
            }
        }
    }
}

QModelIndex MultilevelHeaderView::indexAt(const QPoint& pos)
{
    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(this->model());
    const int nCurOrientation = orientation();
    const int ROWS = tblModel->rowCount();
    const int COLS = tblModel->columnCount();
    int logicalIdx = logicalIndexAt(pos);

    if (nCurOrientation == Qt::Horizontal)
    {
        int dY=0;
        for (int row=0;row<ROWS;++row)
        {
            QModelIndex cellIndex = tblModel->index(row,logicalIdx);
            dY += cellIndex.data(Qt::SizeHintRole).toSize().height();
            if (pos.y() <= dY) return cellIndex;
        }
    }
    else
    {
        int dX=0;
        for (int col=0;col<COLS;++col)
        {
            QModelIndex cellIndex = tblModel->index(logicalIdx,col);
            dX += cellIndex.data(Qt::SizeHintRole).toSize().width();
            if (pos.x() <= dX) return cellIndex;
        }
    }

    return QModelIndex();
}


void MultilevelHeaderView::paintSection(QPainter* painter, const QRect& rect, int logicalIdx) const
{

    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
    const int nCurOrientation = orientation();
    const int nLevelCount = (nCurOrientation == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
    for (int i = 0; i < nLevelCount; ++i)
    {
        QModelIndex cellIndex = (nCurOrientation == Qt::Horizontal) ? tblModel->index(i, logicalIdx) : tblModel->index(logicalIdx, i);
        QSize cellSize = cellIndex.data(Qt::SizeHintRole).toSize();
        QRect sectionRect(rect);

        // set position of the cell
        if (nCurOrientation == Qt::Horizontal)
            sectionRect.setTop(rowSpanSize(logicalIdx,0,i)); // distance from 0 to i-1 rows
        else
            sectionRect.setLeft(columnSpanSize(logicalIdx,0,i));

        sectionRect.setSize(cellSize);

        // check up span column or row
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt  = colSpanIdx.data(eColumnSpanRole).toInt();
            int colSpanTo   = colSpanFrom + colSpanCnt - 1;
            int colSpan = columnSpanSize(cellIndex.row(), colSpanFrom, colSpanCnt);
            if (nCurOrientation == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else
            {
                sectionRect.setLeft(columnSpanSize(logicalIdx,0,colSpanFrom));
                i = colSpanTo;
            }

            sectionRect.setWidth(colSpan);

            // check up  if the column span index has row span
            QVariant subRowSpanData = colSpanIdx.data(eRowSpanRole);
            if (subRowSpanData.isValid())
            {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                int subRowSpan     = rowSpanSize(colSpanFrom,subRowSpanFrom,subRowSpanCnt);
                if (nCurOrientation == Qt::Vertical)
                    sectionRect.setTop(sectionViewportPosition(subRowSpanFrom));
                else
                {
                    sectionRect.setTop(rowSpanSize(colSpanFrom,0,subRowSpanFrom));
                    i = subRowSpanTo;
                }
                sectionRect.setHeight(subRowSpan);
            }
            cellIndex=colSpanIdx;
        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(eRowSpanRole).toInt();
            int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
            int rowSpan     = rowSpanSize(cellIndex.column(),rowSpanFrom,rowSpanCnt);
            if (nCurOrientation == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else
            {
                sectionRect.setTop(rowSpanSize(logicalIdx,0,rowSpanFrom));
                i = rowSpanTo;
            }
            sectionRect.setHeight(rowSpan);

            // check up if the row span index has column span
            QVariant subColSpanData = rowSpanIdx.data(eColumnSpanRole);
            if (subColSpanData.isValid())
            {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                int subColSpan     = columnSpanSize(rowSpanFrom,subColSpanFrom,subColSpanCnt);
                if (nCurOrientation == Qt::Horizontal)
                    sectionRect.setLeft(sectionViewportPosition(subColSpanFrom));
                else
                {
                    sectionRect.setLeft(columnSpanSize(rowSpanFrom,0,subColSpanFrom));
                    i = subColSpanTo;
                }
                sectionRect.setWidth(subColSpan);
            }
            cellIndex=rowSpanIdx;
        }

        // draw section with style
        QStyleOptionHeader sectionStyle;
        initStyleOption(&sectionStyle);
        sectionStyle.textAlignment = Qt::AlignCenter;
        sectionStyle.iconAlignment = Qt::AlignVCenter;
        sectionStyle.section = logicalIdx;
        sectionStyle.text = cellIndex.data(Qt::DisplayRole).toString();
        sectionStyle.rect = sectionRect;

        // file background or foreground color of the cell
        QVariant bg = cellIndex.data(Qt::BackgroundRole);
        QVariant fg = cellIndex.data(Qt::ForegroundRole);
        if (bg.canConvert<QBrush>())
        {
            sectionStyle.palette.setBrush(QPalette::Button, qvariant_cast<QBrush>(bg));
            sectionStyle.palette.setBrush(QPalette::Window, qvariant_cast<QBrush>(bg));
        }
        if (fg.canConvert<QBrush>())
        {
            sectionStyle.palette.setBrush(QPalette::ButtonText, qvariant_cast<QBrush>(fg));
        }

        painter->save();
        qDrawShadePanel(painter,sectionStyle.rect,sectionStyle.palette,false,1,&sectionStyle.palette.brush(QPalette::Button));
        style()->drawControl(QStyle::CE_HeaderLabel, &sectionStyle, painter);
        painter->restore();
    }
}

QSize MultilevelHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    const MultilevelHeaderModel* tblModel = qobject_cast<const MultilevelHeaderModel*>(this->model());
    const int nCurOrientation = orientation();

    const int nLevelCount = (nCurOrientation == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();

    QSize siz = QHeaderView::sectionSizeFromContents(logicalIndex);
    for (int i=0;i<nLevelCount;++i)
    {
        QModelIndex cellIndex = (nCurOrientation == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        siz=cellIndex.data(Qt::SizeHintRole).toSize();

        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt     = colSpanIdx.data(eColumnSpanRole).toInt();
            int colSpanTo   = colSpanFrom + colSpanCnt -1;
            siz.setWidth(columnSpanSize(colSpanIdx.row(),colSpanFrom,colSpanCnt));
            if (nCurOrientation == Qt::Vertical) i = colSpanTo;
        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(eRowSpanRole).toInt();
            int rowSpanTo   = rowSpanFrom + rowSpanCnt-1;
            siz.setHeight(rowSpanSize(rowSpanIdx.column(),rowSpanFrom,rowSpanCnt));
            if (nCurOrientation == Qt::Horizontal) i = rowSpanTo;
        }
    }
    return siz;
}

QModelIndex MultilevelHeaderView::columnSpanIndex(const QModelIndex& currentIdx) const
{
    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
    const int curRow = currentIdx.row();
    const int curCol = currentIdx.column();
    int i = curCol;
    while (i >= 0)
    {
        QModelIndex spanIndex = tblModel->index(curRow,i);
        QVariant span   = spanIndex.data(eColumnSpanRole);
        if (span.isValid() && spanIndex.column()+span.toInt()-1 >= curCol)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

QModelIndex MultilevelHeaderView::rowSpanIndex(const QModelIndex& currentIdx) const
{
    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
    const int curRow = currentIdx.row();
    const int curCol = currentIdx.column();
    int i = curRow;
    while (i >= 0)
    {
        QModelIndex spanIndex = tblModel->index(i,curCol);
        QVariant span   = spanIndex.data(eRowSpanRole);
        if (span.isValid() && spanIndex.row()+span.toInt()-1 >= curRow)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

int MultilevelHeaderView::columnSpanSize(int row, int from, int spanCount) const
{
    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i)
    {
        QSize cellSize = tblModel->index(row,i).data(Qt::SizeHintRole).toSize();
        span += cellSize.width();
    }
    return span;
}


int MultilevelHeaderView::rowSpanSize(int column, int from, int spanCount) const
{
    const MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i)
    {
        QSize cellSize = tblModel->index(i,column).data(Qt::SizeHintRole).toSize();
        span += cellSize.height();
    }
    return span;
}

/**
 * @return section numbers
 */
int MultilevelHeaderView::getSectionRange(QModelIndex& index, int* beginSection, int* endSection) const
{
    // check up section range from the index
    QModelIndex colSpanIdx = columnSpanIndex(index);
    QModelIndex rowSpanIdx = rowSpanIndex(index);

    if (colSpanIdx.isValid())
    {
        int colSpanFrom = colSpanIdx.column();
        int colSpanCnt  = colSpanIdx.data(eColumnSpanRole).toInt();
        int colSpanTo   = colSpanFrom+colSpanCnt-1;
        if (orientation() == Qt::Horizontal)
        {
            *beginSection = colSpanFrom;
            *endSection   = colSpanTo;
            index = colSpanIdx;
            return colSpanCnt;
        }
        else
        {
            // check up  if the column span index has row span
            QVariant subRowSpanData = colSpanIdx.data(eRowSpanRole);
            if (subRowSpanData.isValid())
            {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                *beginSection = subRowSpanFrom;
                *endSection   = subRowSpanTo;
                index = colSpanIdx;
                return subRowSpanCnt;
            }
        }
    }

    if (rowSpanIdx.isValid())
    {
        int rowSpanFrom = rowSpanIdx.row();
        int rowSpanCnt  = rowSpanIdx.data(eRowSpanRole).toInt();
        int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
        if (orientation() == Qt::Vertical)
        {
            *beginSection = rowSpanFrom;
            *endSection   = rowSpanTo;
            index = rowSpanIdx;
            return rowSpanCnt;
        }
        else
        {
            // check up if the row span index has column span
            QVariant subColSpanData = rowSpanIdx.data(eColumnSpanRole);
            if (subColSpanData.isValid())
            {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                *beginSection = subColSpanFrom;
                *endSection   = subColSpanTo;
                index = rowSpanIdx;
                return subColSpanCnt;
            }
        }
    }

    //若为非合并单元格，则为点击当前列
    if (!colSpanIdx.isValid() || !rowSpanIdx.isValid())
    {
        int rowSpanFrom = index.row();
        int colSpanFrom = index.column();

        if (orientation() == Qt::Horizontal)
        {
            *beginSection = colSpanFrom;
            *endSection   = colSpanFrom;
        }
        else
        {
            *beginSection = rowSpanFrom;
            *endSection   = rowSpanFrom;
        }

        return 1;
    }

    return 0;
}


void MultilevelHeaderView::onSectionResized(int logicalIndex,int oldSize,int newSize)
{

    MultilevelHeaderModel* tblModel = qobject_cast<MultilevelHeaderModel*>(this->model());
    const int nCurOrientation = orientation();
    const int nLevelCount = (nCurOrientation == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
    int pos = sectionViewportPosition(logicalIndex);
    int xx  = (nCurOrientation == Qt::Horizontal)?pos:0;
    int yy  = (nCurOrientation == Qt::Horizontal)?0:pos;
    QRect sectionRect(xx,yy,0,0);
    for (int i=0;i<nLevelCount;++i)
    {
        QModelIndex cellIndex = (nCurOrientation == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QSize cellSize=cellIndex.data(Qt::SizeHintRole).toSize();

        // set position of cell
        if (nCurOrientation == Qt::Horizontal)
        {
            sectionRect.setTop(rowSpanSize(logicalIndex,0,i));
            cellSize.setWidth(newSize);
        }
        else
        {
            sectionRect.setLeft(columnSpanSize(logicalIndex,0,i));
            cellSize.setHeight(newSize);
        }
        tblModel->setData(cellIndex,cellSize,Qt::SizeHintRole);

        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);

        if (colSpanIdx.isValid())
        {
            int colSpanFrom = colSpanIdx.column();
            if (nCurOrientation == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else
            {
                sectionRect.setLeft(columnSpanSize(logicalIndex,0,colSpanFrom));
            }

        }
        if (rowSpanIdx.isValid())
        {
            int rowSpanFrom = rowSpanIdx.row();
            if (nCurOrientation == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else
                sectionRect.setTop(rowSpanSize(logicalIndex,0,rowSpanFrom));
        }
        QRect rToUpdate(sectionRect);
        rToUpdate.setWidth(viewport()->width()-sectionRect.left());
        rToUpdate.setHeight(viewport()->height()-sectionRect.top());
        viewport()->update(rToUpdate.normalized());
    }

    if (newSize > 0)
    {
//        DebugInfo << QStringLiteral("表头尺寸") << logicalIndex << oldSize << newSize;

        emit signalSectionSizeChanged(logicalIndex, oldSize, newSize);
    }
}




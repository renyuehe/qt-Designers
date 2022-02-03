#ifndef MULTILEVELHEADERVIEW_H
#define MULTILEVELHEADERVIEW_H

#include <QHeaderView>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QList>


/*多级表头视图类*/
class MultilevelHeaderView: public QHeaderView
{
    Q_OBJECT
public:

    /**
     * @brief MultilevelHeaderView  多级表头构造函数
     * @param orientation   方向
     * @param parent    父窗口
     */
    explicit MultilevelHeaderView(Qt::Orientation orientation = Qt::Horizontal, QWidget* parent = nullptr);

    virtual ~MultilevelHeaderView();

private:

    //保存当前是否调整过最后一列的尺寸
    bool m_bAdjustLastSection;

public:

    /**
     * @brief ZoomToScale 缩放表头
     * @param fScale 比例值 大于1 放大， 小于1缩小
     */
    void ZoomToScale(double dScaleFactor, qreal dFontPointSize);

    /**
     * @brief 根据比例放大
     * @param scale
     */
    void zoomByScale(double scale);

    /**
     * @brief setRowHeight 设置表头指定行行高
     * @param row 指定行
     * @param rowHeight 行高
     */
    void setRowHeight(int row, int rowHeight);

    /**
     * @brief setColumnWidth 设置表头指定列宽
     * @param col 指定列
     * @param colWidth 列宽
     */
    void setColumnWidth(int col, int colWidth);

    void setSpan(int row, int column, int rowSpanCount, int columnSpanCount);
    void setCellBackgroundColor(const QModelIndex& index, const QColor&);
    void setCellForegroundColor(const QModelIndex& index, const QColor&);

    /**
     * @brief setHeaderModel 设置模型函数，根据表头方向，调整尺寸
     * @param pModel 模型
     */
    void setHeaderModel(QAbstractItemModel* pModel);

public slots:

    /**
     * @brief slotResizeLastSection 重设最后一列的宽度，在tree收缩时加1，伸展时减1。实质上是想通过列的resize函数引起整个水平头的位置更新。
     * 不通过这样的处理，在tree的伸展收缩或者整个界面隐藏和展示时会水平头的位置不正确。
     */
    void slotResizeLastSection();

protected:

    // override
    virtual void mousePressEvent(QMouseEvent* event);
    virtual QModelIndex indexAt(const QPoint&);
    virtual void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    // inherent features
    QModelIndex columnSpanIndex(const QModelIndex& currentIndex) const;
    QModelIndex rowSpanIndex(const QModelIndex& currentIndex) const;
    int columnSpanSize(int row, int from, int spanCount) const;
    int rowSpanSize(int column, int from, int spanCount) const;
    int getSectionRange(QModelIndex& index, int* beginSection, int* endSection) const;

protected Q_SLOTS:
    void onSectionResized(int logicalIdx,int oldSize,int newSize);

Q_SIGNALS:
    void sectionPressed(int from, int to);

    /**
     * @brief signalSectionSizeChanged 表格单元格尺寸变化时，通知兄弟表格
     * @param logicalIdx 位置
     * @param oldSize 原尺寸
     * @param newSize 新尺寸
     */
    void signalSectionSizeChanged(int logicalIdx,int oldSize,int newSize);

};

#endif // MULTILEVELHEADERVIEW_H



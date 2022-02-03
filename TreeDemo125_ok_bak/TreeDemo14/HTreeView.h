#ifndef HTreeView_H
#define HTreeView_H

#include <QTreeView>
#include <QPen>
#include <QPainter>

#include <QEvent>
#include <QWheelEvent>

class __declspec(dllexport) HTreeView : public QTreeView
{
    Q_OBJECT
public:
    HTreeView(QWidget *parent = Q_NULLPTR);

protected:
    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const override;

    void drawRow(QPainter * painter, const QStyleOptionViewItem & options, const QModelIndex & index) const override;


    void wheelEvent(QWheelEvent * Event) override;

signals:
    void zoomEvent(bool isIn);

public:

};

#endif // HTreeView_H

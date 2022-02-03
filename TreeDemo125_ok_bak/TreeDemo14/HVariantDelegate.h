#pragma once

#ifndef HVARIANTDELEGATE_H
#define HVARIANTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QPainter>

/////////////////////// 老版 枚举 //////////////////////////////
//单元格类型
enum HItemType {
    directInputType,    //直接输入
    dropdownType,       //下拉选项
    dictionaryType   //字典选项
};

/////////////////////// 新版 枚举 //////////////////////////////
/**已使用 userRole 范围
* @ userRole - 1                : 提示信息
* @ userRole —— userRole+10     : UserRoleExtends
*
* @ userRole+20 —— userRole+30  : CellRoleDetails
* @ userRole+30 —— userRole+40  : DisplayRoleDetails
* @ userRole+40 —— userRole+50  : DescribeRoleDetails
**/
namespace HVarientItemSpace
{
    /**
     * @brief 用于替代 Qt::UserRole 、Qt::UserRole+1 、 Qt::UserRole+2 、 Qt::UserRole+3
     */
    enum UserRoleExtends
    {
        CellTypeRole = Qt::UserRole,
        CellPopupWindowRolt,//提供UserRole+10的控件可用于用户自动扩充子窗口  对应 CellPopupWindowType
        PopupWindowCategoryRole,//对应 字典类型
        PopupWindowLogicRole,//对应 MultiTreeWidgetLogicType
    };
    /**
     * @brief 对应 Qt::UserRole+1 或 (HVarientItemSpace::UserRoleExtends::CellTypeRole)
     */
    enum CellPopupWindowType
    {
        MultiTreeWidgetType,
        MultiTableWidgetType,
        CustomWidgetType
    };

    /**
     * @brief 对应 Qt::UserRole+2 或 (HVarientItemSpace::UserRoleExtends::CellTypeRole)
     */
    enum MultiTreeWidgetCategoryType{
        majorType,//专业
        siteType,//地点
        categoryType,//类别
    };

    /**
     * @brief 当 Qt::Displayrole == true 枚举生效
     */
    enum DisplayRoleDetails
    {
        DisplayContent = Qt::UserRole+30,//内容
        DisplayAlignment,//对齐
        DisplayFont,//字体
        DisplayColor,//颜色
        DisplayFontSize,//字体大小
    };

    /**
     * @brief 当 HVarientItemSpace::CellRoleDetails::describeRole == true 枚举生效
     */
    enum DescribeRoleDetails
    {
        DescribeContent = Qt::UserRole+40,//内容
        DescribeAlignment,//对齐
        DescribeFont,//字体
        DescribeColor,//颜色
        DescribeFontSize,//字体大小
    };

}

class __declspec(dllexport) HVariantDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    //////////// 共性函数 /////////////
    explicit HVariantDelegate(QObject * parent = nullptr);


    ~HVariantDelegate() override;

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    /**
     * @brief 获取 display描述 或 Describe描述
     * @param [in]index
     * @param [out]font
     * @param [out]color
     * @param [out]aliType
     * @param [out]str
     */
    void getIndexTextInfos(const QModelIndex &index, QFont &font, QColor & color, int &aliType, QString &str);
public:

};


#endif // HVARIANTDELEGATE_H

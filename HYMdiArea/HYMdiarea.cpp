#include "HYMdiArea.h"

HYMdiArea::HYMdiArea(bool isUseAnimation, QWidget *parent , Qt::WindowFlags f)
    : QFrame(parent, f)
{
    m_mdiArea.useAnimation = isUseAnimation;
    this->setLayout(&layout);
    layout.addWidget(&m_mdiArea);

    connect(&m_mdiArea, &QMdiArea::subWindowActivated, this, [&](QMdiSubWindow *window){
        Q_UNUSED(window)
        this->updateStates();
    });
}

HYMdiArea::~HYMdiArea()
{
}

void HYMdiArea::updateStates()
{
    m_mdiArea.updateStates();
}

QMdiSubWindow *HYMdiArea::addSubWindow(QWidget *widget, QString title, const QSize &size)
{
    if(widget){
        widget->setWindowTitle(title);
        QMdiSubWindow * subWindow = m_mdiArea.addSubWindow(widget);

        subWindow->resize(size);
        updateStates();//组合窗口的好处就在这里,addSubWindow之后还要走一些其他地方的函数,避免了派生重写最多只能在return之前调用的问题  为什么！！！！！ bug
        return subWindow;
    }
    else
        return nullptr;
}

void HYMdiArea::setSubWindowViewMode(HMdiArea::SubWindowViewMode mode)
{
    m_mdiArea.setSubWindowViewMode(mode);
}

void HYMdiArea::setSubWindowSize(const QSize &size)
{
    if(!size.isEmpty()){
        QList<QMdiSubWindow *> &&subWidgetList = m_mdiArea.subWindowList();
        for(auto iter : subWidgetList){
            iter->resize(size);
        }
        updateStates();
    }
}

void HYMdiArea::setAnimationEnable(const bool isUseAnimation)
{
    this->m_mdiArea.useAnimation = isUseAnimation;
    updateStates();
}

void HYMdiArea::setAnimationTime(const int durationTime, const int spacingTime)
{
    this->m_mdiArea.animationDurationTime = durationTime;
    this->m_mdiArea.animationSubwinSpacingTime = spacingTime;
}

void HYMdiArea::setAnimationCurveMode(const QEasingCurve::Type curveMode)
{
    this->m_mdiArea.curveMode = curveMode;
}

void HYMdiArea::setSubWidgetsOption(const QMdiSubWindow::SubWindowOption &option)
{
    QList<QMdiSubWindow *> subWindowList = m_mdiArea.subWindowList();
    for (auto iter : subWindowList) {
        iter->setOption(option);
    }
}

void HYMdiArea::mouseReleaseEvent(QMouseEvent *event)
{
    m_mdiArea.updateStates();
    QFrame::mouseReleaseEvent(event);
}

void HYMdiArea::setSubWidgetsKeyboardSingleStep(int step)
{
    QList<QMdiSubWindow *> subWindowList = m_mdiArea.subWindowList();
    for (auto iter : subWindowList) {
        iter->setKeyboardSingleStep(step);
    }
}

void HYMdiArea::setSubWidgetsKeyboardPageStep(int step)
{
    QList<QMdiSubWindow *> subWindowList = m_mdiArea.subWindowList();
    for (auto iter : subWindowList) {
        iter->setKeyboardPageStep(step);
    }
}

void HYMdiArea::setTabPosition(QTabWidget::TabPosition position)
{
    m_mdiArea.setTabPosition(position);
}

void HYMdiArea::setTabsMovable(bool movable)
{
    m_mdiArea.setTabsMovable(movable);
}

void HYMdiArea::setBackground(const QBrush &background)
{
    m_mdiArea.setBackground(background);
}

void HYMdiArea::setTabsClosable(bool closable)
{
    m_mdiArea.setTabsClosable(closable);
}

void HYMdiArea::setActivationOrder(QMdiArea::WindowOrder order)
{
    m_mdiArea.setActivationOrder(order);
};




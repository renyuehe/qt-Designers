#ifndef DEFINE_H
#define DEFINE_H

#include <QVector>

//学生信息
typedef struct _STUDENT{
    QString name;   //姓名
    int score1;     //语文成绩
    int score2;     //数学成绩
    int score3;     //外语成绩
    _STUDENT()
    {
        name = "";
        score1 = score2 = score3 = 0;
    }
}STUDENT,*PSTUDENT;

//班级信息
typedef struct _CLASS{
    QString name;   //班级
    QVector<STUDENT*> students;
    _CLASS()
    {
        name = "";
    }
}CLASS;


class HGlobalZoom;

static HGlobalZoom * m_pHGlobalZoom = nullptr;

class HGlobalZoom
{
public:
    static HGlobalZoom * getinstance()
    {
        if(m_pHGlobalZoom)
        {
            return m_pHGlobalZoom;
        }
        else
        {
            m_pHGlobalZoom = new HGlobalZoom;
            return m_pHGlobalZoom;
        }
    }

    inline void update()
    {
        zoomScalePercent = numerator/denominator;
    }

    //普通缩小
    void zommIn(){
        if(setNumerator(numerator / 1.1))
            update();
    }
    //自定义缩小
    void zoomInCustom(double x){
        if(setNumerator(numerator / x))
            update();
    }

    //普通放大
    void zommOut(){
        if(setNumerator(numerator * 1.1))
        update();
    }

    //自定义放大
    void zoomOutCustom(double x){
        if(setNumerator(numerator * x))
            update();
    }


    /**
     * @brief 当前放大比例
     * @return
     */
    double getZoomScalePercent()
    {
        return zoomScalePercent;
    }

    double getCurrentNumerator()
    {
        return numerator;
    }

private:
    bool setNumerator(double number)
    {
        if(number > 10  & number < 1000)//可以小10倍 放大100倍
        {
            numerator = number;
            return true;
        }
        else if(number < 10)
        {
            numerator = 10;
            return false;
        }
        else if(number > 1000)
        {
            numerator = 1000;
            return false;
        }
        else {
            return false;
        }
    }
private:
    double numerator;//分子
    double denominator;//分母 (没用用 double 是因为考虑效率问题,double计算可能整体上会变慢)
    double zoomScalePercent;  //全局缩放百分比

    HGlobalZoom():
        numerator(100),
        denominator(100),
        zoomScalePercent(numerator/denominator)
    {}
};

#include <QColor>
//表头单元格数据
struct HeaderItem{
    int nStartRow;  //水平位置
    int nStartColumn;  //垂直位置
    int nRowSpan;   //行跨越
    int nColumnSpan;    //列跨越
    QString strContent; //内容
    QColor color;   //前景色
    QColor bgColor; //背景色

    HeaderItem(){
       nStartRow = 0;
       nStartColumn = 0;
       nRowSpan = 0;
       nColumnSpan = 0;
       strContent = "";
       color = Qt::black;
       bgColor = Qt::white;
    }

    HeaderItem(QString content, int posX, int posY, int rowSpan, int colunmSpan)
    {
       nStartRow = posX;
       nStartColumn = posY;
       nRowSpan = rowSpan;
       nColumnSpan = colunmSpan;
       strContent = content;
       color = QColor(0,0,0);
       bgColor = QColor(230, 236, 243);
    }
};


#endif // DEFINE_H


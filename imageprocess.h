#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <math.h>

#include "common.h"

class ShowResultWidget : public QWidget
{
    Q_OBJECT
public:
    ShowResultWidget(QWidget *parent=0);

    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        Lift,
        Right,
        Up,
        Down,
        Move
    }; // 操作的枚举类型

    int m_count;
    float x;
    QTimer* m_Timer;

    QList<float> xList_1;
    QList<float> yList_1;
    QList<float> xList_2;
    QList<float> yList_2;

    std::vector<float> range1;
    std::vector<float> range2;
    cv::Mat image_show;
    int show_col_0;
    int show_row_0;
    int show_col;
    int show_row;

    bool haveData1;
    bool haveData2;
    bool haveDraw;


    cv::Mat AddAxes(cv::Mat inputMat);

private :
    DrawAxes drawAxes;
    int matrix_size;

    QPixmap  *pix;
    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    float ratio;                //比例
    QPoint offset;              //一次的图片偏移值
    QPoint Alloffset;           //总偏移
    QLabel *size_label;

    QPushButton  *BigButton;
    QPushButton  *LittleButton;
    QPushButton  *LeftButton;
    QPushButton  *RightButton;
    QPushButton  *UpButton;
    QPushButton  *DownButton;

    bool isInitialPose;
    bool isDataOnline;
    bool isReset;

    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件

    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

private slots:

    void ReceiveData_lidar1(bool, std::vector<float> range1); // 接受雷达1数据
    void ReceiveData_lidar2(bool, std::vector<float> range2); // 接受雷达2数据
    void draw(std::string, std::string, double, double, double, double, double, double); // 画图操作
    void ClearImage(); // 清除图像

    // 图像界面的按钮使能与失能
    void EnableButton();
    void DisableButton();

    // 图像操作按钮的触发函数
    void onUpClicked();
    void onDownClicked();
    void OnLeftClicked();
    void OnRightClicked();
    void onLittleClicked();
    void onBigClicked();

protected:
    void paintEvent(QPaintEvent *);

    QVBoxLayout *mainlayout;
    QLabel *mergePicture;

};

#endif // IMAGEPROCESS_H

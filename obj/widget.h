#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QMediaPlayer>
#include<QMenu>
#include<QDesktopWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected slots:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void changePicture() ; //定时器函数
    void on_acction_trigered1();  //点击菜单 关于的响应
    void on_acction_trigered2();  //点击菜单 退出的响应

private:
    Ui::Widget *ui;
    QPoint point;

    QPixmap *pix;
    QTimer timer;
    QString idle[8];  //站着的照片
    int idleNum;  //计数

    QString attack[9];  // 射箭图片
    int attackNum;  //用于计数 选择图片 射箭

    QString run[8];  //跑步的图片
    int runNum;   //用于记录跑步

    QString death[11];  //死亡图片
    int deathNum;   //鼠标点击死亡

    QString damage[4];  //鼠标点击害羞图片
    int damageNum;

    QString music[10];  //存放音乐的播放路径
    QMediaPlayer * player;

    int choise;  //用于选择播放那种照片

     int timeLong;   //运动时间的长度
    int x;  //跑的坐标
    int y;

    QMenu *pMenu; //右键弹出菜单
    QPoint mousePosP;
    QDesktopWidget * pDesktopWidget;
    int dsx; //桌面的边缘
    int dsy;

};

#endif // WIDGET_H

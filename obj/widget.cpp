#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <synchapi.h>
#include <QBitmap>
#include <QDebug>
#include <QMessageBox>  //程序退出提示窗口

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //窗口最大化 获取最大窗口的大小
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();  //屏幕区域
    dsx = screenRect.width();
    dsy = screenRect.height();
     this->setMinimumSize( dsx,dsy);
     this->setMaximumSize(dsx,dsy);
     this->setWindowTitle("小美同学");
     this->setWindowIcon(QIcon(":/pic/windows/top.png"));  //窗口的图标

     move(0,0);

    //显示第一张照片
    pix = new QPixmap();
    pix->load(":/pic/idle/0000.png",nullptr);
    resize(pix->size());  //图片的大小

    // setMask(QBitmap(pix->mask()));  //不显示图片之外的透明部分
    //去掉边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //将背景设置为透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    //定时器
    timer.start(200);
    connect(&timer,SIGNAL(timeout()),this,SLOT(changePicture()));//定时器溢出关联changePicture()函数

    //站着的照片 idle
    idle[0] = ":/pic/idle/0000.png";
    idle[1] = ":/pic/idle/0001.png";
    idle[2] = ":/pic/idle/0002.png";
    idle[3] = ":/pic/idle/0003.png";
    idle[4] = ":/pic/idle/0004.png";
    idle[5] = ":/pic/idle/0005.png";
    idle[6] = ":/pic/idle/0006.png";
    idle[7] = ":/pic/idle/0007.png";
    idleNum = 0;

    //加载图片 attack射箭
    attack[0] = ":/pic/attack/0000.png";
    attack[1] = ":/pic/attack/0001.png";
    attack[2] = ":/pic/attack/0002.png";
    attack[3] = ":/pic/attack/0003.png";
    attack[4] = ":/pic/attack/0004.png";
    attack[5] = ":/pic/attack/0005.png";
    attack[6] = ":/pic/attack/0006.png";
    attack[7] = ":/pic/attack/0007.png";
    attack[8] = ":/pic/attack/0008.png";
    attackNum = 0;

    //加载跑步的图片 run
    run[0] = ":/pic/run/0000.png";
    run[1] = ":/pic/run/0001.png";
    run[2] = ":/pic/run/0002.png";
    run[3] = ":/pic/run/0003.png";
    run[4] = ":/pic/run/0004.png";
    run[5] = ":/pic/run/0005.png";
    run[6] = ":/pic/run/0006.png";
    run[7] = ":/pic/run/0007.png";
    runNum = 0;

    //死亡图片加载
    death[0] = ":/pic/dead/0000.png";
    death[1] = ":/pic/dead/0001.png";
    death[2] = ":/pic/dead/0002.png";
    death[3] = ":/pic/dead/0003.png";
    death[4] = ":/pic/dead/0004.png";
    death[5] = ":/pic/dead/0005.png";
    death[6] = ":/pic/dead/0006.png";
    death[7] = ":/pic/dead/0007.png";
    death[8] = ":/pic/dead/0008.png";
    death[9] = ":/pic/dead/0009.png";
    death[10] =":/pic/dead/0010.png";
    deathNum = 0;

    //鼠标点击害羞图片
    damage[0] = ":/pic/damage/0000.png";
    damage[1] = ":/pic/damage/0001.png";
    damage[2] = ":/pic/damage/0002.png";
    damage[3] = ":/pic/damage/0003.png";
    damageNum = 0;

    choise = 0;  //开始显示站着
    timeLong = 0;
    //出现起始坐标
    x = 680;
    y = 380;


    //音乐播放
    player = new QMediaPlayer(this);
    music[0] = "../music/menu.mp3";  //打开菜单的音乐

    //创建弹出菜单对象
    pMenu = new QMenu(this);
    //添加活动1
     QAction *pAction1= new  QAction (pMenu);
     pAction1->setText("关于");   //设置文字
      pMenu->addAction(pAction1);  //action 添加到menu中
    //添加活动2
    QAction *pAction2 = new  QAction (pMenu);
    pAction2->setText("退出");   //设置文字
    //pAction2->setIcon(QIcon("."));  //设置图标
    pMenu->addAction(pAction2);  //action 添加到menu中

    //关联事件响应函数，选择菜单中的action后·，触发槽函数执行
    connect(pAction1,SIGNAL(triggered()),this,SLOT(on_acction_trigered1()));
    connect(pAction2,SIGNAL(triggered()),this,SLOT(on_acction_trigered2()));
}

Widget::~Widget()
{
    delete ui;
    delete pix;
}


void Widget::changePicture()
{
    //站着
    timer.start(190);
    if (choise == 0)
    {
        if (idleNum == 8 )
        {
            idleNum =0;

        }
        //运动时间长短
        if (timeLong == 20 )
        {
            //切换到射箭
            choise = 1;
            timeLong =0;
        }
        else
        {
            QImage image(idle[idleNum]);
            QImage mirrored(bool horizontal = false, bool vertical = true);
            pix->load(idle[idleNum],nullptr);
            resize(pix->size());
             idleNum++;
             timeLong++;
        }
    }
    //射箭
    else if (choise == 1)
    {
        timer.start(200);

        if (attackNum == 8)
        {
            attackNum = 0;
            //切换到跑
            choise = 2;
        }
        else
        {
            pix->load(attack[attackNum],nullptr);
            resize(pix->size());
            attackNum ++;
        }
    }
    //跑步图片加载
   else if(choise == 2)
    {
        timer.start(130);
        if ( x <= dsx)
        {
            x += 10;
        }
        else
        {
            x = -55;
        }

        if( y <= dsy)
        {
            y +=3;
        }
        else
        {
            y = -30;
        }

       if (runNum == 7)
       {
           runNum = 0;

       }

       if (timeLong == 50 )
       {
           choise = 0;  //切换到射箭
           timeLong = 0;
       }
       else
       {
           pix->load(run[runNum],nullptr);
           resize(pix->size());
           runNum++;
           timeLong++;
       }

    }
    //死亡
    else if (choise == 3)
    {
        timer.start(200);
        if ( deathNum < 11)
        {
            pix->load(death[deathNum],nullptr);
            resize(pix->size());
             deathNum++;
        }
        else
        {
            timer.stop();
            deathNum = 0;
            pix->load(death[10],nullptr);
            resize(pix->size());
        }


    }
    //鼠标点击害羞图片
    else if(choise == 4)
    {
        timer.start(150);
        if ( damageNum == 3)
        {
            damageNum = 0;
            //切换到站着
            choise = 0;
        }
        else
        {
            pix->load(damage[damageNum],nullptr);
            resize(pix->size());
            damageNum++;
         }
    }

    //更新
    update();

}



void Widget::paintEvent(QPaintEvent *)
{

       QPainter p(this);
       p.drawPixmap(x,y,*pix);


}

//鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        timer.stop();
        pix->load(":/pic/drag/0000.png",nullptr);
        resize(pix->size());
        x = e->globalX();
        y = e->globalY();
    }
    update();

}

//鼠标点击事件
void Widget::mousePressEvent(QMouseEvent *e)
{

    //点击鼠标左键
    if(e->button() == Qt::LeftButton)
    {
        //记录鼠标点击的次数
        deathNum++;

        //鼠标点击次数过多
        if (deathNum > 15)
        {
                choise = 3;
        }
        else
        {
               //害羞
               choise = 4;
        }

        //获得差值
        point = e->globalPos()-this->frameGeometry().topLeft();
         e->accept();

    }
    //中间键按下
    else if(e->button() == Qt::MidButton)
    {

    }
    //右键被按下 跳出菜单
    else
    {
        timer.stop();
        //打开菜单的音乐
        player->setMedia(QUrl::fromLocalFile (music[0]));
        player->setVolume(80); //音量
        player->play();

        //显示菜单
        mousePosP = e->pos();  //mousePosP 全局变量，QPoint
        //QPointF mouseLocPos = e->localPos();  //获得指针当前的相对地址，同pos()
        //QPoint mouseGlobePos = e->globalPos();  //获得指针当前的绝对地址，相对屏幕左上角
        //执行弹出操作
        pMenu->popup(e->globalPos());
    }

    update();
}

//鼠标释放
void Widget::mouseReleaseEvent(QMouseEvent *)
{
    timer.start(50);
}

//点击 菜单中活动响应函数
void Widget::on_acction_trigered1()
{
    QMessageBox message(QMessageBox::NoIcon,tr("关于"),tr("版本：小美同学1.0  "  ));
    message.setIconPixmap(QPixmap(":/pic/idle/0000.png"));
    message.exec();

}

//点击 菜单中活动响应函数
void Widget::on_acction_trigered2()
{
    //关闭
    if ( !(QMessageBox::information(this,tr("退出"),tr("小美舍不得你！真的要离开吗？"),tr("关闭"),tr("取消"))))
    {
         this->close();
    }

}



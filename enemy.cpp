#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<QImage>
#include"waypoint.h"
#include<mainwindow.h>
#include<cmath>
Enemy::Enemy()
{

}
Enemy::Enemy(waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite):QObject(0),e_pos(startWayPoint->pos()),e_sprite(sprite)
{
    e_maxHP=40;
    e_currentHP=40;
    e_active=false;
    e_walkspeed=1.0;
    e_desWayPoint=startWayPoint->nextWayPoint();
    e_rotationSprite=0.0;
    e_game=game;
}

void Enemy::draw(QPainter *painter){
    QImage ima;
    ima.load(":/pictures/soldier.png");
    painter->drawImage(e_pos.x(),e_pos.y(),ima,150,80,120,70);
}

inline bool Enemy::collisionCircle(QPoint point1, int r1, QPoint point2, int r2){
    double disX=point1.x()-point2.x();
    double disY=point1.y()-point2.y();
    int dis=sqrt(disX*disX+disY*disY);
    if(dis<r1+r2)return true;
    else return false;

}
void Enemy::move(){//多态实现
    if(!e_active)return;
    if(e_desWayPoint->nextWayPoint()){
        e_pos=e_desWayPoint->pos();
        e_desWayPoint=e_desWayPoint->nextWayPoint();
    }
    else{
        e_game->gameLose=true;//游戏失败
        e_game->removeEnemy(this);//移走敌人
        return;
    }

}
void Enemy::do_Activate(){
    e_active=true;
}

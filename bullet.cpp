#include "bullet.h"
#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QPainter>

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               MainWindow *game, const QPixmap &sprite )
{

}


void Bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 100;

    QPropertyAnimation *animation = new QPropertyAnimation(this,"xx");
    animation->setDuration(duration);
    animation->setStartValue(b_towerPos);
    animation->setEndValue(b_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet::hitTarget() {
    if (b_game->enemyList().indexOf(b_target)!=-1) {
        //b_target.getDamaged(b_attackdamage);
    }
    b_game->removeBullet(this);
}

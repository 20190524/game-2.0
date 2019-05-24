#include "tower.h"
#include "bullet.h"

#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>


const QSize Tower::fixedSize(63,63);

Tower::Tower(QPoint pos,MainWindow *game,const QPixmap &sprite):
    t_sprite(sprite),
    t_pos(pos),
    t_game(game) {
    t_attackBreakTimer=new QTimer(this);
    connect(t_attackBreakTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete t_attackBreakTimer;
    t_attackBreakTimer=NULL;
}

void Tower::attackEnemy() {
    t_attackBreakTimer->start(t_attackBreak);
}



void Tower::drawTower(QPainter *painter) {
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(t_pos,t_attackRange,t_attackRange);
    //攻击范围的绘制

    static const QPoint offsetPoint (-fixedSize.width()/2,-fixedSize.height()/2);
    painter->translate(t_pos);
    painter->drawPixmap(offsetPoint,t_sprite);
    painter->restore();
}

void Tower::chooseEnemyforAttack(Enemy *enemy) {
    t_chooseEnemy = enemy;
    attackEnemy();
    //t_chooseEnemy.getattacked(); 敌人类-确定被攻击的函数；
}

void Tower::enemyKilled() {
    if (t_chooseEnemy) {
        t_chooseEnemy = NULL;
        t_attackBreakTimer->stop();
        t_rotationSprite=0.0;
    }
}

void Tower::loseSightofEnmey() {
    //t_chooseEnemy.losesight();敌人类-离开攻击范围的函数；
    if (t_chooseEnemy) {
        t_chooseEnemy = NULL;
        t_attackBreakTimer->stop();
        t_rotationSprite=0.0;
    }
}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(t_pos, /*t_chooseEnemy.pos()*/ t_attackDamage, t_chooseEnemy, t_game);
    bullet->move();
    t_game->addBullet(bullet);
}





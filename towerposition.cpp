#include "towerposition.h"
#include <QPainter>

const  QSize towerposition:: fixedSize(65,65);

towerposition::towerposition(QPoint pos,const QPixmap & sprite ):
    t_pos(pos),
    t_haveTower(false),
    t_sprite(sprite)
{

}

const QPoint towerposition::centerPos() {
    QPoint offsetpoint(fixedSize.width()/2,fixedSize.height()/2);
    return t_pos+offsetpoint;
}

bool towerposition::containTower(const QPoint &pos) {
    bool X=(t_pos.x()<pos.x())&&(pos.x()<(t_pos.x()+fixedSize.width()));
    bool Y=(t_pos.y()<pos.y())&&(pos.y()<(t_pos.y())+fixedSize.height());
    return X&&Y;
}

bool towerposition::canhaveTower(){
    return t_haveTower;
}

void towerposition::drawTower(QPainter *painter) const {
    painter->drawPixmap(t_pos.x(),t_pos.y(),t_sprite);
}

void towerposition::sethaveTower() {
    t_haveTower=true;
}

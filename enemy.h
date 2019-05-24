#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class waypoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy: public QObject
{
    Q_OBJECT
public:
    Enemy(waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/pictures/soldier.png"));
    void draw(QPainter *painter);
    void move();
    inline bool collisionCircle(QPoint point1,int r1,QPoint point2,int r2);
protected slots:
    void do_Activate();
private:
    double e_walkspeed;
    int e_currentHP;
    int e_maxHP;
    bool e_active;
    double e_rotationSprite;

    waypoint * e_desWayPoint;
    QPoint e_pos;
    const QPixmap e_sprite;
    MainWindow * e_game;
    static const QSize fixedSize;
};

#endif // ENEMY_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "enemy.h"
#include<QTimer>

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadTowerPositions();
    bool canbuyTower() const;
    void removeEnemy(Enemy *enemy);
    void removeBullet(Bullet *bullet);
    QList<Enemy *> enemyList() const;
    void addwaypoint();
    bool loadWaves();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void upDateMap();
private:
    int waves=0;//敌人波数
    bool gameWin=false;
    bool gameLose=false;

    Ui::MainWindow *ui;
    QList<Tower *> t_towerlist;
    QList<towerposition> t_towerpositionlist;
    QList<Enemy *> enemylist;
    QList<Bullet *> bulletlist;
    QList<waypoint *> waypointlist;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTowerPositions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pictures/bg1.png"));

    foreach (const towerposition &towerPos, t_towerpositionlist) {
        towerPos.drawTower(&painter);
    }
    foreach (Tower *tower,t_towerlist) {
        tower->drawTower(&painter);
    }
    if (gameWin==true) {
        painter.drawPixmap(0,0,QPixmap("win map"));
    }
    if (gameLose==true) {
        painter.drawPixmap(0,0,QPixmap("lose map"));
    }
    if(loadWaves()==true){
        foreach (Enemy*enemy, enemylist) enemy->draw(&painter);
    }
}

bool MainWindow::canbuyTower() const {
    return true;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint pressPos=event->pos();
    auto it=t_towerpositionlist.begin();
    while (it!=t_towerpositionlist.end()) {
        if (canbuyTower()&&it->containTower(pressPos)&&(!it->canhaveTower())) {
            it->sethaveTower();
            Tower *tower=new Tower (it->centerPos(),this);
            t_towerlist.push_back(tower);
            update();
            break;
        }
        ++it;
    }
}

void MainWindow::loadTowerPositions() {
    QPoint pos[]={
        QPoint(100, 480),
        QPoint(200, 480),
        QPoint(380, 400),
        QPoint(380, 300),
        QPoint(380, 200),
        QPoint(620, 220),
        QPoint(780, 350),
        QPoint(300, 480),
        QPoint(950, 350),
        QPoint(950, 450),
        QPoint(950, 550),
        QPoint(550, 350)	};
    int len	= sizeof(pos) / sizeof(pos[0]);
    for (int i = 0; i < len; ++i)
        t_towerpositionlist.push_back(pos[i]);

}

void MainWindow::removeEnemy(Enemy *enemy) {
    Q_ASSERT(enemy);
    enemylist.removeOne(enemy);
    if (enemylist.empty()) {
        waves++;
        if (!loadWaves()) {
            gameWin=true;
        }
    }
}

QList<Enemy *> MainWindow::enemyList() const {
    return enemylist;
}

void MainWindow::removeBullet(Bullet *bullet) {
    Q_ASSERT(bullet);

    bulletlist.removeOne(bullet);
    delete bullet;
}

void MainWindow::addwaypoint() {
    waypoint *wayPoint1 = new waypoint(QPoint(420, 285));
    waypointlist.push_back(wayPoint1);

    waypoint *wayPoint2 = new waypoint(QPoint(35, 285));
    waypointlist.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    waypoint *wayPoint3 = new waypoint(QPoint(35, 195));
    waypointlist.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    waypoint *wayPoint4 = new waypoint(QPoint(445, 195));
    waypointlist.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    waypoint *wayPoint5 = new waypoint(QPoint(445, 100));
    waypointlist.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    waypoint *wayPoint6 = new waypoint(QPoint(35, 100));
    waypointlist.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

bool MainWindow::loadWaves(){
    if(waves>=6){
        return false;
    }
    waypoint*startpoint=waypointlist.back();
    int enemyInterval[]={100,500,600,1000,3000,6000};
    for(int i=0;i<6;i++){
        Enemy *enemy=new Enemy(startpoint,this);
        enemylist.push_back(enemy);
        QTimer::singleShot(enemyInterval[i],enemy,SLOT(do_Activate()));
    }
    return true;
}
void MainWindow::upDateMap(){
    foreach (Enemy*enemy, enemylist)
        enemy->move();
    update();
}

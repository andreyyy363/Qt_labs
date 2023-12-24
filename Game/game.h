#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsView>
#include "gamefield.h"
#include <QInputDialog>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>
#include <QKeyEvent>
#include "player.h"
#include "enemy.h"
#include "food.h"


namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    void startNewGame();
    void setNewGameValues();
    ~Game();

private slots:
    void on_actionSettings_triggered();
    void updateGame();
    void moveEnemies();

private:
    Ui::Game *ui;

    int fieldSize;
    int cellSize;
    int enemyCount;
    int foodCount;
    int speedCount;
    int playerEnergy;
    int targetFoodCount;

    Player *player;
    GameField *gameField;

    void keyPressEvent(QKeyEvent *event) override;
    void deleteObjects();

    QVector<Enemy*> enemies;
    QVector<Food*> foods;
    QVector<QVector<bool>> occupiedCells;

    QTimer *gameTimer, *enemyMoveTimer;
    QPair<int, int> addRandomObject(GameObject *object);
};

#endif // GAME_H

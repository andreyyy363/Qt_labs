#include "game.h"
#include "settings.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);


    setNewGameValues();
    startNewGame();
}

void Game::startNewGame()
{
    // Create and customize the playing field
    gameField = new GameField(fieldSize, cellSize);
    ui->view->setSceneRect(0, 0, fieldSize * cellSize, fieldSize * cellSize);
    ui->view->setScene(gameField);

    occupiedCells = QVector<QVector<bool>>(fieldSize, QVector<bool>(fieldSize, false));
    // Add a player to the grid
    player = new Player(fieldSize, cellSize);
    player->setFocus();

    QPair<int, int> playerPos = addRandomObject(player);
    player->setGridPos(playerPos.first, playerPos.second);

    // Add enemies to the grid
    for (int i = 0; i < enemyCount; ++i)
    {
        Enemy *enemy = new Enemy(fieldSize, cellSize);
        QPair<int, int> enemyPos = addRandomObject(enemy);
        enemy->setGridPos(enemyPos.first, enemyPos.second);
        enemies.append(enemy);
    }

    // Add food to the grid
    for (int i = 0; i < foodCount; ++i)
    {
        Food *food = new Food();
        QPair<int, int> foodPos = addRandomObject(food);
        food->setGridPos(foodPos.first, foodPos.second);
        foods.append(food);
    }

    // Timer for enemy movement
    enemyMoveTimer = new QTimer(this);
    connect(enemyMoveTimer, &QTimer::timeout, this, &Game::moveEnemies);
    enemyMoveTimer->start(speedCount);


    // Timer to update the game
    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
    gameTimer->start(100);
}
// Move each enemy
void Game::moveEnemies()
{
    for (Enemy *enemy : enemies)
        enemy->moveRandomly(foods, enemies);
}

QPair<int, int> Game::addRandomObject(GameObject *object)
{
    int x, y;
    do {
        x = QRandomGenerator::global()->bounded(fieldSize);
        y = QRandomGenerator::global()->bounded(fieldSize);
    } while (occupiedCells[x][y]);  // Repeat until we find a free cell

    gameField->addObjectToGrid(object, x, y);
    occupiedCells[x][y] = true;  // Mark the cell as occupied

    return qMakePair(x, y);  // Return cell coordinates
}

void Game::updateGame()
{
    // Check if there is food in the same cell as the player.
    for (int i = 0; i < foods.size(); ++i) {
        if (foods[i]->getGridX() == player->getGridX() && foods[i]->getGridY() == player->getGridY())
        {
            // Remove food and decrease the food counter
            delete foods[i];
            foods.removeAt(i);
            foodCount--;
            break;
        }
    }

    for (Enemy *enemy : enemies)
    {
        // Check if the enemy has collided with the player
        if (enemy->getGridX() == player->getGridX() && enemy->getGridY() == player->getGridY())
        {
            // Take one life from the player
            player->energyDecrement();
            gameField->removeItem(player);
            // Move the player to a random place on the field
            QPair<int, int> playerPos = addRandomObject(player);
            player->setGridPos(playerPos.first, playerPos.second);
        }
    }

    // Set life and food count on Labels in Ui
    ui->energyCount->setText("x" + QString::number(player->getEnergy()));
    ui->foodCount->setText("x" + QString::number(foodCount));

    // If we run out of food, stop the game and display a victory message
    if (foodCount == 0)
    {
        gameTimer->stop();
        enemyMoveTimer->stop();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Win", "Congratulations! You won the game. Do you want to start a new game?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            deleteObjects();
            setNewGameValues();
            startNewGame();
        }
        else
            QApplication::quit();

        return;
    }

    // If the player has less than one life, stop the game and display a loss message
    if (player->getEnergy() < 1)
    {
        gameTimer->stop();
        enemyMoveTimer->stop();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Over", "You lost the game. Do you want to start a new game?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            deleteObjects();
            setNewGameValues();
            startNewGame();
        }
        else
            QApplication::quit();

        return;
    }
}

void Game::deleteObjects()
{
    delete player;
    for (Enemy *enemy : enemies)
        delete enemy;

    enemies.clear();
    for (Food *food : foods)
        delete food;

    foods.clear();
    delete gameField;
}

void Game::setNewGameValues()
{
    Settings set;
    set.show();
    if (set.exec() == QDialog::Accepted)
    {
        fieldSize = set.getFieldSize();
        cellSize = set.getCellSize();
        enemyCount = set.getEnemiesNumber();
        foodCount = set.getFoodNumber();
        speedCount = set.getSpeed();
    }
    else
        QApplication::quit();
}

void Game::on_actionSettings_triggered()
{
    // Suspend the game
    gameTimer->stop();
    enemyMoveTimer->stop();

    Settings set;
    set.show();
    if (set.exec() == QDialog::Accepted)
    {
        fieldSize = set.getFieldSize();
        cellSize = set.getCellSize();
        enemyCount = set.getEnemiesNumber();
        foodCount = set.getFoodNumber();
        speedCount = set.getSpeed();

        deleteObjects();
        startNewGame();
    }
    else
    {
        // If there are no changes, resume the game
        gameTimer->start(100);
        enemyMoveTimer->start(speedCount);
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P)
    {
        if (gameTimer->isActive())
        {
            // If the timer is active (the game is running), stop it
            gameTimer->stop();
            enemyMoveTimer->stop();
            player->setCanMove(false);  // Block the player's movement

            // Display the pause message
            QMessageBox::information(this, tr("Game paused"), tr("Game paused. Press P to continue this game."));
        }
        else
        {
            // If the timer is not active (the game is paused), start it
            gameTimer->start(100);
            enemyMoveTimer->start(speedCount);
            player->setCanMove(true);  // Unlock player movement

            // Display a message that the game is resuming
            QMessageBox::information(this, tr("Game continues"), tr("Game continues. Press P to pause this game."));
        }
    }

    player->keyPressEvent(event);
    gameField->keyPressEvent(event);
}

Game::~Game()
{
    delete ui;
}

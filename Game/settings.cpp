#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->fieldSize, SIGNAL(valueChanged(int)), this, SLOT(updateMaxValues(int)));
    updateMaxValues(ui->fieldSize->value());
}

const int Settings::getFieldSize()
{
    return ui->fieldSize->value();
}
const int Settings::getCellSize()
{
    return ui->cellSize->value();
}
const int Settings::getEnemiesNumber()
{
    return ui->numbEnemies->value();
}
const int Settings::getFoodNumber()
{
    return ui->numbFood->value();
}
const int Settings::getSpeed()
{
    return ui->speed->value();
}

// Update the maximum values of spinboxes
void Settings::updateMaxValues(int fieldSize)
{
    int maxEnemies = fieldSize * fieldSize / 4;
    int maxFood = fieldSize * fieldSize / 2;


    ui->numbEnemies->setMaximum(maxEnemies);
    ui->numbFood->setMaximum(maxFood);
}

Settings::~Settings()
{
    delete ui;
}

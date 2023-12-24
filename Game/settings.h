#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

    const int getFieldSize();
    const int getCellSize();
    const int getEnemiesNumber();
    const int getFoodNumber();
    const int getSpeed();
    ~Settings();

private slots:
    void updateMaxValues(int fieldSize);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H

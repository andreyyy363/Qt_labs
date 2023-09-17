#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QButtonGroup>

#include <QDebug>
#include <string>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QComboBox *comboBoxInput1, *comboBoxInput2;

    QCheckBox *invertCheckBox;

    QPushButton *clearButton, *convertButton;



    QRadioButton *weight, *length, *time;
    QGroupBox *radioGroup;
    QVBoxLayout *radioVBox;

    QSpinBox *textSizeSpinBox;
    
    QLabel *directionLabel, *label, *backgroundLabel;

    QLineEdit *inputLine1, *inputLine2;

    QProgressBar *progressBar;

    QButtonGroup *logicalGroup;

    QIntValidator *validator;


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots :
    double convert_weight(double input, QString input_type, QString output_type);
    double convert_length(double input, QString input_type, QString output_type);
    double convert_time(double input, QString input_type, QString output_type);

    void radioToggle(int id, bool checked);
    void convertPressed(int id, bool checked, bool inverted);
    void change_direction(int state);
    void clear_lines();
    void update_text_size(int value);



};
#endif // WIDGET_H

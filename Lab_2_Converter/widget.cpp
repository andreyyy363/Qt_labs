#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //Set window
    this->setWindowTitle("Converter");
    this->setWindowIcon(QIcon(":/img/icon.png"));
    this->setFixedSize(500, 500);

    //Decorative labels
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/img/background.png"));
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());

    label = new QLabel("Converter v1.0", this);
    label->setFixedSize(440, 50);
    label->move(30, 30);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 0, 0, 164), stop:1 rgba(255, 0, 0, 164)); "
                         "color: rgb(255, 255, 255); font-size: 30px; font-weight: bold;");

    //Direction label
    directionLabel = new QLabel("->", this);
    directionLabel->setStyleSheet("color: blue;");
    directionLabel->setAlignment(Qt::AlignCenter);
    directionLabel->setFixedSize(100, 50);
    directionLabel->move(200, 100);

    //CheckBox
    invertCheckBox = new QCheckBox("Invert", this);
    invertCheckBox->move(225, 150);
    invertCheckBox->setFixedSize(100, 50);
    invertCheckBox->setStyleSheet("color: yellow;");
    connect(invertCheckBox, &QCheckBox::stateChanged, this, &Widget::change_direction);

    //SpinBox
    textSizeSpinBox = new QSpinBox(this);
    textSizeSpinBox->setSingleStep(2);
    textSizeSpinBox->move(200, 240);
    textSizeSpinBox->setRange(12, 48);
    textSizeSpinBox->setFixedSize(100, 30);
    connect(textSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &Widget::update_text_size);

    //ProgressBar
    progressBar = new QProgressBar(this);
    progressBar->move(150, 300);
    progressBar->setFixedWidth(200);
    progressBar->setRange(12, 48);
    progressBar->setTextVisible(false);

    //ComboBoxes
    comboBoxInput1 = new QComboBox(this);
    comboBoxInput1->setFixedSize(100, 50);
    comboBoxInput1->move(30, 150);

    comboBoxInput2 = new QComboBox(this);
    comboBoxInput2->setFixedSize(100, 50);
    comboBoxInput2->move(370, 150);

    //Buttons
    convertButton = new QPushButton("Convert", this);
    convertButton->move(30, 240);
    convertButton->setFixedSize(100, 30);
    connect(convertButton, &QPushButton::clicked, this, [=]()
    {
        convertPressed(logicalGroup->checkedId(), logicalGroup->checkedButton() != nullptr, invertCheckBox->isChecked());
    });

    clearButton = new QPushButton("Clear", this);
    connect(clearButton, &QPushButton::clicked, this, &Widget::clear_lines);
    clearButton->move(370, 240);
    clearButton->setFixedSize(100, 30);

    //LineEdits
    inputLine1 = new QLineEdit(this);
    inputLine1->setFixedSize(100, 50);
    inputLine1->move(30, 100);

    inputLine2 = new QLineEdit(this);
    inputLine2->setFixedSize(100, 50);
    inputLine2->move(370, 100);

    validator = new QIntValidator(this);
    inputLine1->setValidator(validator);
    inputLine2->setValidator(validator);

    //RadioGroup and RadioButtons
    weight = new QRadioButton("Weight", this);
    length = new QRadioButton("Length", this);
    time = new QRadioButton("Time", this);

    radioGroup = new QGroupBox(this);
    radioGroup->setTitle("Convert type");
    radioGroup->setStyleSheet("color: yellow;");
    radioGroup->setFixedSize(100, 100);
    radioGroup->move(200, 350);

    radioVBox = new QVBoxLayout;
    radioVBox->addWidget(weight);
    radioVBox->addWidget(length);
    radioVBox->addWidget(time);

    radioGroup->setLayout(radioVBox);

    logicalGroup = new QButtonGroup(this);
    logicalGroup->addButton(weight, 1);
    logicalGroup->addButton(length, 2);
    logicalGroup->addButton(time, 3);

    connect(logicalGroup, &QButtonGroup::idToggled, this, &Widget::radioToggle);
    weight->setChecked(true);
}

double Widget::convert_weight(double input, QString input_type, QString output_type)
{
    double grams;

    if (input_type == "t")
        grams = input * 1000000.0;
    if (input_type == "q")
        grams = input * 100000.0;
    if (input_type == "kg")
        grams = input * 1000.0;
    if (input_type == "g")
        grams = input;
    if (input_type == "mg")
        grams = input / 1000.0;
    if (input_type == "lb")
        grams = input * 453.59237;

    if (output_type == "t")
        return grams / 1000000.0;
    if (output_type == "q")
        return grams / 100000.0;
    if (output_type == "kg")
        return grams / 1000.0;
    if (output_type == "g")
        return grams;
    if (output_type == "mg")
        return grams * 1000.0;
    if (output_type == "lb")
        return grams / 453.59237;

}

double Widget::convert_length(double input, QString input_type, QString output_type)
{
    double meters;

    if (input_type == "km")
        meters = input * 1000.0;
    if (input_type == "m")
        meters = input;
    if (input_type == "dm")
        meters = input / 10.0;
    if (input_type == "cm")
        meters = input / 100.0;
    if (input_type == "mm")
        meters = input / 1000.0;
    if (input_type == "mi")
        meters = input * 1609.344;

    if (output_type == "km")
        return meters / 1000.0;
    if (output_type == "m")
        return meters;
    if (output_type == "dm")
        return meters * 10.0;
    if (output_type == "cm")
        return meters * 100.0;
    if (output_type == "mm")
        return meters * 1000.0;
    if (output_type == "mi")
        return meters / 1609.344;
}

double Widget::convert_time(double input, QString input_type, QString output_type)
{
    double seconds;

    if (input_type == "y")
        seconds = input * 31536000.0;
    if (input_type == "wk")
        seconds = input * 604800.0;
    if (input_type == "d")
        seconds = input * 86400.0;
    if (input_type == "h")
        seconds = input * 3600.0;
    if (input_type == "min")
        seconds = input * 60.0;
    if (input_type == "s")
        seconds = input;
    if (input_type == "ms")
        seconds = input / 1000.0;

    if (output_type == "y")
        return seconds * 31536000.0;
    if (output_type == "wk")
        return seconds / 604800.0;
    if (output_type == "d")
        return seconds / 86400.0;
    if (output_type == "h")
        return seconds / 3600.0;
    if (output_type == "min")
        return seconds / 60.0;
    if (output_type == "s")
        return seconds;
    if (output_type == "ms")
        return seconds * 1000.0;
}

void Widget::change_direction(int state)
{
    if (state == Qt::Checked)
        directionLabel->setText("<-");
    else
        directionLabel->setText("->");
}


void Widget::convertPressed(int id, bool checked, bool inverted)
{
    if(checked)
    {
        double input, output;

        if(inverted)
            input = inputLine2->text().toDouble();
        else
            input = inputLine1->text().toDouble();
        if(id == 1)
        {
            if(inverted)
                output = convert_weight(input, comboBoxInput2->currentText(), comboBoxInput1->currentText());
            else
                output = convert_weight(input, comboBoxInput1->currentText(), comboBoxInput2->currentText());
        }
        if(id == 2)
        {
            if(inverted)
                output = convert_length(input, comboBoxInput2->currentText(), comboBoxInput1->currentText());
            else
                output = convert_length(input, comboBoxInput1->currentText(), comboBoxInput2->currentText());
        }
        if(id == 3)
        {
            if(inverted)
                output = convert_time(input, comboBoxInput2->currentText(), comboBoxInput1->currentText());
            else
                output = convert_time(input, comboBoxInput1->currentText(), comboBoxInput2->currentText());
        }
        if(inverted)
            inputLine1->setText(QString::number(output, 'g', 16));
        else
            inputLine2->setText(QString::number(output, 'g', 16));
    }


}

void Widget::radioToggle(int id, bool checked)
{
    if(checked)
    {
        comboBoxInput1->clear();
        comboBoxInput2->clear();

        if(id == 1)
        {
            comboBoxInput1->addItems({"t", "q", "kg", "g", "mg", "lb"});
            comboBoxInput2->addItems({"t", "q", "kg", "g", "mg", "lb"});
        }

        if(id == 2)
        {
            comboBoxInput1->addItems({"km", "m", "dm", "cm", "mm", "mi"});
            comboBoxInput2->addItems({"km", "m", "dm", "cm", "mm", "mi"});
        }

        if(id == 3)
        {
            comboBoxInput1->addItems({"y", "wk", "d", "h", "min", "s", "ms"});
            comboBoxInput2->addItems({"y", "wk", "d", "h", "min", "s", "ms"});

        }
    }
}

void Widget::clear_lines()
{
    inputLine1->clear();
    inputLine2->clear();

    if(invertCheckBox->isChecked())
        invertCheckBox->setChecked(false);

    textSizeSpinBox->setValue(12);
    weight->setChecked(true);

}

void Widget::update_text_size(int value)
{
    inputLine1->setStyleSheet(QString("font-size: %1px").arg(QString::number(value)));
    inputLine2->setStyleSheet(QString("font-size: %1px").arg(QString::number(value)));

    directionLabel->setStyleSheet(QString("font-size: %1px; color: blue;").arg(QString::number(value)));

    progressBar->setValue(value);
}

Widget::~Widget()
{
}


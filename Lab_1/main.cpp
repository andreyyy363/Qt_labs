#include "widget.h"
#include <QtWidgets>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(320, 240);
    w.setWindowTitle("Lab_1");

    QPushButton *troll_button = new QPushButton("Press me", &w);
    troll_button->move(120, 10);
    troll_button->show();

    QObject::connect(troll_button, &QPushButton::clicked, [&w, troll_button]() {
        troll_button->setFixedSize(50, 50);
        troll_button->setText("");
        troll_button->setIcon(QIcon(":/trollface/trollface.png"));
        troll_button->setIconSize(troll_button->size());

        int maxX = w.width() - troll_button->width();
        int maxY = w.height() - troll_button->height();
        int newX = rand() % maxX;
        int newY = rand() % maxY;

        troll_button->move(newX, newY);
        troll_button->show();
    });

    QPushButton *show_label_button = new QPushButton("Show label", &w);
    show_label_button->move(120, 160);
    show_label_button->show();

    QPushButton *hide_label_button = new QPushButton("Hide label", &w);
    hide_label_button->move(120, 200);
    hide_label_button->show();

    QLabel label("Text Label");
    QPushButton button("Button");
    QLineEdit textedit;
    QHBoxLayout layout;
    layout.addWidget(&label);
    layout.addWidget(&button);
    layout.addWidget(&textedit);
    w.setLayout(&layout);

    label.hide();
    button.hide();
    textedit.hide();

    QObject::connect(show_label_button, &QPushButton::clicked, [&label, &button, &textedit]() {
        label.show();
        button.show();
        textedit.show();
    });

    QObject::connect(hide_label_button, &QPushButton::clicked, [&label, &button, &textedit]() {
        label.hide();
        button.hide();
        textedit.hide();
    });

    w.show();
    return a.exec();
}

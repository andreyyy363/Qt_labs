#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QColorDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QRandomGenerator>
#include <QPainterPath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveImage();
    void saveAsImage();
    void close();

    void draw();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void chooseOutlineColor();
    void chooseFillColor();
    void chooseAirbrushColor();
    void setPen();

    void updateLabels();


    // void updateBrushInfo(const QBrush &brush, int size, const QColor &color);

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;

    int x = -1, y = -1;
    int prevX = -1, prevY = -1;
    enum brushes{CURVE, CIRCLE, POLYGON, AIRBRUSH, CONTOUR};
    int brushIndex = -1;

    QPainter *painter;

    QWidget *curveWidget, *figureWidget, *airbrushWidget;
    QVBoxLayout *curveLayout, *figureLayout, *airbrushLayout;
    
    QSlider *curveThicknessSlider, *outlineThicknessSlider, *radiusSlider, *airbrushRadiusSlider;

    QComboBox *lineTypeBox;
    QSpinBox *pixelBox;

    QPushButton *curveColorButton, *fillColorButton, *outlineColorButton, *airbrushColorButton;
    
    QLabel *thicknessLabel, *radiusLabel, *lineTypeLabel, *airbrushRadiusLabel, *pixelLabel;

    QColor color, fillColor, airbrushColor;

    QPen pen;

    QString filename;
};
#endif // MAINWINDOW_H

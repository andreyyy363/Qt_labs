#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPixmap>
#include <QImage>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVector2D>


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenuBar *menuBar;
    QMenu *file;
    QToolBar *toolBar;
    QAction *fileOpen , *fileSave, *fileExit;
    QAction *apply, *discard, *grayscale, *sepia, *invert, *pixelize, *twist, *brightness, *monochrome, *logarithm, *binarization;
    QLabel *label, *title;
    QSpinBox *cellSize;
    QSlider *twistSlider, *monochromeSlider, *brightnessSlider, *binarizationSlider;
    QDoubleSpinBox *logarithmSpinBox;
    QCheckBox *invertMonochrome;
    QPushButton *color1Button, *color2Button;
    QVBoxLayout *layout, *dockLayout;
    QPixmap pixmap;
    QImage image, imgCopy;
    QWidget *centralWidget, *dockLayoutWidget;
    QDockWidget *dockWidget;
    QColor color1, color2;
    QList<QWidget*> widgets;

private slots:
    void hideWidgets();
    void open();
    void save();
    void close();
    void applyChanges();
    void discardChanges();
    void drawImage();

    void grayscaleImg();
    void sepiaImg();
    void invertImg();
    void pixelizeImg();
    void twistImg();
    void monochromeImg();
    void brightnessImg();
    void logarithmImg();
    void chooseColor1();
    void chooseColor2();
    void binarizationImg();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

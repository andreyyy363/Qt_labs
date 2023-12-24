#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showMaximized();

    ui->toolBar->hide();
    ui->dockWidget->hide();
    ui->save->setDisabled(true);
    ui->saveAs->setDisabled(true);

    fillColor = QColor(Qt::transparent);

    //////////////////////////////////////////
    /////////////// CurveBrush ///////////////
    //////////////////////////////////////////

    curveWidget = new QWidget(ui->dockWidget);

    ////////// Thickness //////////

    // ThicknessLabel
    thicknessLabel = new QLabel("Thickness", curveWidget);
    thicknessLabel->setFixedHeight(50);
    thicknessLabel->setAlignment(Qt::AlignCenter);
        thicknessLabel->setStyleSheet("color: rgb(255, 140, 0); font: 700 20pt 'Segoe UI'; text-decoration: underline;");

    //ThicknessSlider
    curveThicknessSlider = new QSlider(Qt::Horizontal, curveWidget);
    curveThicknessSlider->setRange(1, 100);
    curveThicknessSlider->setSingleStep(1);
    connect(curveThicknessSlider, &QSlider::actionTriggered, this, &MainWindow::setPen);

    ////////// Colors //////////
    curveColorButton = new QPushButton("Color", curveWidget);
    connect(curveColorButton, &QPushButton::clicked, this, &MainWindow::chooseOutlineColor);


    ////////// Curve Layout //////////
    curveLayout = new QVBoxLayout();
    curveLayout->addWidget(thicknessLabel);
    curveLayout->addWidget(curveThicknessSlider);
    curveLayout->addWidget(curveColorButton);

    curveWidget->setLayout(curveLayout);
    ui->dockLayot->addWidget(curveWidget);

    curveWidget->hide();


    ////////////////////////////////////////////
    /////////////// Circle Brush ///////////////
    ////////////////////////////////////////////

    figureWidget = new QWidget(ui->dockWidget);

    ////////// Thickness //////////

    // ThicknessLabel
    thicknessLabel = new QLabel("Thickness", figureWidget);
    thicknessLabel->setFixedHeight(50);
    thicknessLabel->setAlignment(Qt::AlignCenter);
    thicknessLabel->setStyleSheet("color: rgb(0, 170, 0); font: 700 20pt 'Segoe UI'; text-decoration: underline;");

    //ThicknessSlider
    outlineThicknessSlider = new QSlider(Qt::Horizontal, figureWidget);
    outlineThicknessSlider->setRange(1, 20);
    outlineThicknessSlider->setSingleStep(1);
    connect(outlineThicknessSlider, &QSlider::actionTriggered, this, &MainWindow::setPen);

    ////////// Radius //////////

    // RadiusLabel
    radiusLabel = new QLabel("Radius", figureWidget);
    radiusLabel->setFixedHeight(50);
    radiusLabel->setAlignment(Qt::AlignCenter);
    radiusLabel->setStyleSheet("color: rgb(0, 0, 205); font: 700 20pt 'Segoe UI'; text-decoration: underline;");

    //RadiusSlider
    radiusSlider = new QSlider(Qt::Horizontal, figureWidget);
    radiusSlider->setRange(1, 100);
    radiusSlider->setSingleStep(1);
    connect(radiusSlider, &QSlider::actionTriggered, this, &MainWindow::setPen);

    ////////// Colors //////////

    // OutlineColor
    outlineColorButton = new QPushButton("Outline color", figureWidget);
    connect(outlineColorButton, &QPushButton::clicked, this, &MainWindow::chooseOutlineColor);

    // FillColor
    fillColorButton = new QPushButton("Fill color", figureWidget);
    connect(fillColorButton, &QPushButton::clicked, this, &MainWindow::chooseFillColor);

    ////////// Line Type //////////

    // LineTypeLabel
    lineTypeLabel = new QLabel("Line type", figureWidget);
    lineTypeLabel->setFixedHeight(50);
    lineTypeLabel->setAlignment(Qt::AlignCenter);
    lineTypeLabel->setStyleSheet("color: rgb(72, 61, 139); font: 700 20pt 'Segoe UI'; text-decoration: underline;");


    // LineTypeComboBox
    lineTypeBox = new QComboBox(ui->dockWidget);
    lineTypeBox->addItem("Solid line");
    lineTypeBox->addItem("Dotted");
    lineTypeBox->addItem("Dashed");
    lineTypeBox->addItem("Dash-dotted");

    connect(lineTypeBox, &QComboBox::currentIndexChanged, this, &MainWindow::setPen);

    ////////// Circle Layout //////////
    figureLayout = new QVBoxLayout();

    figureLayout->addWidget(radiusLabel);
    figureLayout->addWidget(radiusSlider);
    figureLayout->addWidget(outlineColorButton);
    figureLayout->addWidget(fillColorButton);
    figureLayout->addWidget(lineTypeLabel);
    figureLayout->addWidget(lineTypeBox);
    figureLayout->addWidget(thicknessLabel);
    figureLayout->addWidget(outlineThicknessSlider);


    figureWidget->setLayout(figureLayout);
    ui->dockLayot->addWidget(figureWidget);

    figureWidget->hide();

    ////////////////////////////////////////
    /////////////// Airbrush ///////////////
    ////////////////////////////////////////
    ///
    airbrushWidget = new QWidget(ui->dockWidget);

    airbrushRadiusLabel = new QLabel("Airbrush radius", airbrushWidget);
    airbrushRadiusLabel->setFixedHeight(50);
    airbrushRadiusLabel->setAlignment(Qt::AlignCenter);
    airbrushRadiusLabel->setStyleSheet("color: rgb(255, 20, 147); font: 700 20pt 'Segoe UI'; text-decoration: underline;");

    airbrushRadiusSlider = new QSlider(Qt::Horizontal, airbrushWidget);
    airbrushRadiusSlider->setRange(1, 100);
    airbrushRadiusSlider->setSingleStep(1);
    connect(airbrushRadiusSlider, &QSlider::actionTriggered, this, &MainWindow::updateLabels);

    pixelLabel = new QLabel("Number of pixels", airbrushWidget);
    pixelLabel->setFixedHeight(50);
    pixelLabel->setAlignment(Qt::AlignCenter);
    pixelLabel->setStyleSheet("color: rgb(0, 128, 128); font: 700 20pt 'Segoe UI'; text-decoration: underline;");

    pixelBox = new QSpinBox(airbrushWidget);
    pixelBox->setRange(1, 1000);
    pixelBox->setSingleStep(1);
    connect(pixelBox, &QSpinBox::valueChanged, this, &MainWindow::updateLabels);

    airbrushColorButton = new QPushButton("Airbrush color", airbrushWidget);
    connect(airbrushColorButton, &QPushButton::clicked, this, &MainWindow::chooseAirbrushColor);

    airbrushLayout = new QVBoxLayout();

    airbrushLayout->addWidget(airbrushRadiusLabel);
    airbrushLayout->addWidget(airbrushRadiusSlider);
    airbrushLayout->addWidget(pixelLabel);
    airbrushLayout->addWidget(pixelBox);
    airbrushLayout->addWidget(airbrushColorButton);

    airbrushWidget->setLayout(airbrushLayout);
    ui->dockLayot->addWidget(airbrushWidget);

    airbrushWidget->hide();

    ////////// Actions //////////
    connect(ui->open, &QAction::triggered, this, &MainWindow::openImage);
    connect(ui->save, &QAction::triggered, this, &MainWindow::saveImage);
    connect(ui->saveAs, &QAction::triggered, this, &MainWindow::saveAsImage);
    connect(ui->exit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->curveBrush, &QAction::triggered, this, [=]()
    {
        brushIndex = CURVE;
        curveWidget->show();
        figureWidget->hide();
        airbrushWidget->hide();
        setPen();
    });

    connect(ui->circleBrush, &QAction::triggered, this, [=]()
    {
        brushIndex = CIRCLE;
        figureWidget->show();
        curveWidget->hide();
        airbrushWidget->hide();
        setPen();
    });

    connect(ui->polygonBrush, &QAction::triggered, this, [=]()
    {
        brushIndex = POLYGON;
        figureWidget->show();
        curveWidget->hide();
        airbrushWidget->hide();
        setPen();
    });

    connect(ui->airbrush, &QAction::triggered, this, [=]()
    {
        brushIndex = AIRBRUSH;
        airbrushWidget->show();
        figureWidget->hide();
        curveWidget->hide();
        updateLabels();
    });

    connect(ui->contour, &QAction::triggered, this, [=]()
    {
        brushIndex = CONTOUR;
        airbrushWidget->hide();
        figureWidget->hide();
        curveWidget->hide();
        updateLabels();
    });
}

void MainWindow::openImage()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Image files (*.png *.jpg *.jpeg *.bmp)"));
    pixmap.load(filename);
    if (pixmap.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1").arg(QDir::toNativeSeparators(filename)));
        return;
    }

    ui->toolBar->show();
    ui->dockWidget->show();
    ui->save->setEnabled(true);
    ui->saveAs->setEnabled(true);

    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size()));

    painter = new QPainter(&pixmap);
}

void MainWindow::saveImage()
{
    qDebug() << filename;
    pixmap.save(filename);
}

void MainWindow::saveAsImage()
{
    filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                tr("PNG files (*.png);;JPG files (*.jpg);;JPEG files (*.jpg);;BMP files (*.bmp)"));
    if (pixmap.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
                             tr("Cannot save %1").arg(QDir::toNativeSeparators(filename)));
        return;
    }
    else
        pixmap.save(filename);
}

void MainWindow::close()
{
    if (QMessageBox::question(this, "Exit Dialog", "Do you really want to exit?") == QMessageBox::StandardButton::Yes)
        QApplication::quit();
}

void MainWindow::draw()
{
    if (!pixmap.isNull())
    {
        switch (brushIndex)
        {
            case CURVE:
                painter->drawLine(prevX, prevY, x, y);
                break;
            case CIRCLE:
                painter->drawEllipse(QPoint(x, y), radiusSlider->value(), radiusSlider->value());
                break;
            case POLYGON:
            {
                QPolygon hexagon;
                for (int i = 0; i < 6; ++i)
                {
                    double angle = 60 * i;
                    double x1 = x + radiusSlider->value() * cos(angle * M_PI / 180.0);
                    double y1 = y + radiusSlider->value() * sin(angle * M_PI / 180.0);
                    hexagon << QPoint(x1, y1);
                }

                painter->drawPolygon(hexagon);
                break;
            }
            case AIRBRUSH:
            {
                int numPoints = pixelBox->value();
                for (int i = 0; i < numPoints; ++i)
                {
                    double angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
                    double radius = airbrushRadiusSlider->value() * sqrt(QRandomGenerator::global()->generateDouble());
                    double dx = radius * cos(angle);
                    double dy = radius * sin(angle);

                    painter->drawPoint(x + dx, y + dy);
                }
                break;
            }
            case CONTOUR:
            {
                QPainterPath path;

                // Рисуем лицо
                path.addEllipse(QPoint(x, y), 50, 50);

                // Рисуем глаза
                QPainterPath eyesPath;
                eyesPath.addEllipse(QPointF(x - 15, y - 15), 5, 5);
                eyesPath.addEllipse(QPointF(x + 15, y - 15), 5, 5);

                // Рисуем рот с помощью cubicTo()
                QPainterPath mouthPath;
                mouthPath.moveTo(x - 30, y + 20);
                mouthPath.cubicTo(x - 20, y + 40, x + 20, y + 40, x + 30, y + 20);

                // Рисуем нос
                path.moveTo(x, y);
                QRectF rect(x - 5, y, 10, 10);
                double startAngle = -180;
                double spanAngle = -180;
                path.arcTo(rect, startAngle, spanAngle);

                // Рисуем линию под носом
                path.moveTo(x - 5, y + 5);
                path.lineTo(x + 5, y + 5);

                painter->setPen(QPen(Qt::black));

                // Заливаем лицо
                painter->setBrush(Qt::yellow);
                painter->drawPath(path);

                // Заливаем глаза
                painter->setBrush(Qt::blue);
                painter->drawPath(eyesPath);

                // Заливаем рот
                painter->setBrush(Qt::red);
                painter->drawPath(mouthPath);
                ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size()));

                break;
        }

        default:
            break;
        }
        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size()));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = ui->imageLabel->mapFromGlobal(event->globalPosition());

        x = pos.x() * pixmap.width() / ui->imageLabel->width();
        y = pos.y() * pixmap.height() / ui->imageLabel->height();

        if (brushIndex != CURVE)
        {
            draw();
        }

        prevX = x;
        prevY = y;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF widgetPos = ui->imageLabel->mapFromGlobal(event->globalPosition());

        x = widgetPos.x() * pixmap.width() / ui->imageLabel->width();
        y = widgetPos.y() * pixmap.height() / ui->imageLabel->height();

        if (brushIndex == CURVE || brushIndex == AIRBRUSH)
        {
            draw();
        }

        prevX = x;
        prevY = y;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        brushIndex = -1;
        curveWidget->hide();
        figureWidget->hide();
        airbrushWidget->hide();
        updateLabels();
        ui->brushInfo->setText("");
    }
}

void MainWindow::setPen()
{
    int thick = 1;
    if (brushIndex == CURVE)
    {
        thick = curveThicknessSlider->value();
        pen = QPen(color, thick);
    }

    if (brushIndex == CIRCLE || brushIndex == POLYGON)
    {
        thick = outlineThicknessSlider->value();
        pen = QPen(color, thick);
        Qt::PenStyle selectedStyle = Qt::SolidLine;
        int index = lineTypeBox->currentIndex();
        if (index == 0)
            selectedStyle = Qt::SolidLine;
        if (index == 1)
            selectedStyle = Qt::DashLine;
        if (index == 2)
            selectedStyle = Qt::DotLine;
        if (index == 3)
            selectedStyle = Qt::DashDotLine;

        QBrush fillBrush(fillColor);
        painter->setBrush(fillBrush);
        pen.setStyle(selectedStyle);
    }

    if (brushIndex == AIRBRUSH)
        pen = QPen(airbrushColor);

    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    updateLabels();
}

void MainWindow::chooseOutlineColor()
{
    QColor outlineColor = QColorDialog::getColor(color, this, "Choose brush color");
    if (outlineColor.isValid())
    {
        color = outlineColor;
        setPen();
    }
}

void MainWindow::chooseFillColor()
{
    QColor fcolor = QColorDialog::getColor(color, this, "Choose fill color");
    if (fcolor.isValid())
    {
        fillColor = fcolor;
        setPen();
    }
}

void MainWindow::chooseAirbrushColor()
{
    QColor acolor = QColorDialog::getColor(color, this, "Choose fill color");
    if (acolor.isValid())
    {
        airbrushColor = acolor;
        setPen();
    }
}

void MainWindow::updateLabels()
{
    QPixmap penPixmap(ui->currentBrush->width(), ui->currentBrush->height());
    penPixmap.fill(Qt::transparent);

    QPainter painter(&penPixmap);
    if (brushIndex == CIRCLE || brushIndex == POLYGON)
    {
        QBrush fillBrush(fillColor);
        painter.setBrush(fillBrush);
    }

    if (brushIndex == AIRBRUSH)
        pen = QPen(airbrushColor);

    painter.setPen(pen);

    if (brushIndex == CURVE)
    {
        painter.drawLine(0, penPixmap.height() / 2, penPixmap.width(), penPixmap.height() / 2);
        ui->brushInfo->setText("Curve brush\nThickness: " + QString::number(curveThicknessSlider->value()));
    }

    if (brushIndex == CIRCLE)
    {
        painter.drawEllipse(penPixmap.rect().center(), radiusSlider->value(), radiusSlider->value());
        ui->brushInfo->setText("Circle brush\nThickness: " + QString::number(outlineThicknessSlider->value())
                               + " | Radius: " + QString::number(radiusSlider->value()));
    }

    if (brushIndex == POLYGON)
    {
        QPolygon hexagon;
        for (int i = 0; i < 6; ++i)
        {
            double angle = 60 * i;
            double x = radiusSlider->value() * cos(angle * M_PI / 180.0);
            double y = radiusSlider->value() * sin(angle * M_PI / 180.0);
            hexagon << QPoint(penPixmap.rect().center().x() + x, penPixmap.rect().center().y() + y);
        }


        // Рисуем шестиугольник
        painter.drawPolygon(hexagon);

        ui->brushInfo->setText("Hexagon brush\nThickness: " + QString::number(outlineThicknessSlider->value())
                               + " | Radius: " + QString::number(radiusSlider->value()));
    }

    if (brushIndex == AIRBRUSH)
    {
        int numPoints = pixelBox->value();
        for (int i = 0; i < numPoints; ++i) {
            double angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
            double radius = airbrushRadiusSlider->value() * sqrt(QRandomGenerator::global()->generateDouble());
            double dx = radius * cos(angle);
            double dy = radius * sin(angle);

            painter.drawPoint(penPixmap.rect().center().x() + dx, penPixmap.rect().center().y() + dy);
        }
        ui->brushInfo->setText("Airbrush\nNumber of pixels: " + QString::number(pixelBox->value())
                               + " | Radius: " + QString::number(airbrushRadiusSlider->value()));
    }

    if (brushIndex == CONTOUR)
    {
        QPointF center = penPixmap.rect().center();

        QPainterPath path;

        path.addEllipse(center, 50, 50);

        QPainterPath eyesPath;
        eyesPath.addEllipse(QPointF(center.x() - 15, center.y() - 15), 5, 5);
        eyesPath.addEllipse(QPointF(center.x() + 15, center.y() - 15), 5, 5);

        QPainterPath mouthPath;
        mouthPath.moveTo(center.x() - 30, center.y() + 20);
        mouthPath.cubicTo(center.x() - 20, center.y() + 40, center.x() + 20, center.y() + 40, center.x() + 30, center.y() + 20);

        path.moveTo(center.x(), center.y());
        QRectF rect(center.x() - 5, center.y(), 10, 10);
        double startAngle = -180;
        double spanAngle = -180;
        path.arcTo(rect, startAngle, spanAngle);

        path.moveTo(center.x() - 5, center.y() + 5);
        path.lineTo(center.x() + 5, center.y() + 5);

        painter.setPen(QPen(Qt::black));

        painter.setBrush(Qt::yellow);
        painter.drawPath(path);

        painter.setBrush(Qt::blue);
        painter.drawPath(eyesPath);

        painter.setBrush(Qt::red);
        painter.drawPath(mouthPath);
        ui->brushInfo->setText("Contour smile");
    }

    ui->currentBrush->setPixmap(penPixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "qapplication.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Image Editor v.1.0");
    this->setWindowIcon(QIcon(":/img/icon.png"));
    this->resize(1500,800);

    //Label
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    label->setLineWidth(2);
    layout = new QVBoxLayout();
    layout->addWidget(label);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    //DockWidget
    dockWidget = new QDockWidget("Edit", this);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    dockWidget->setFixedSize(QSize(200, 200));
    this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    dockWidget->hide();
    dockLayoutWidget = new QWidget(this);
    dockLayout = new QVBoxLayout;

    //Sliders

    //Twist slider
    twistSlider = new QSlider(Qt::Horizontal, dockWidget);
    twistSlider->setRange(-360, 360);
    twistSlider->setTickInterval(1);
    twistSlider->setValue(0);
    connect(twistSlider, &QSlider::valueChanged, this, &MainWindow::twistImg);

    //Monochrome slider
    monochromeSlider = new QSlider(Qt::Horizontal, dockWidget);
    monochromeSlider->setRange(0, 2);
    monochromeSlider->setTickInterval(1);
    connect(monochromeSlider, &QSlider::valueChanged, this, &MainWindow::monochromeImg);

    //Brightness slider
    brightnessSlider = new QSlider(Qt::Horizontal, dockWidget);
    brightnessSlider->setRange(-255, 255);
    brightnessSlider->setTickInterval(1);
    brightnessSlider->setValue(0);
    connect(brightnessSlider, &QSlider::valueChanged, this, &MainWindow::brightnessImg);

    //Binarization slider
    binarizationSlider = new QSlider(Qt::Horizontal, dockWidget);
    binarizationSlider->setRange(0, 255);
    binarizationSlider->setTickInterval(1);
    connect(binarizationSlider, &QSlider::valueChanged, this, &MainWindow::binarizationImg);

    //Label for dockWidget
    title = new QLabel(dockWidget);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 16px; font-weight: bold;");

    //SpinBoxes
    cellSize = new QSpinBox(dockWidget);
    cellSize->setRange(1, 100);
    cellSize->setSingleStep(1);
    connect(cellSize, &QSpinBox::textChanged, this, &MainWindow::pixelizeImg);

    logarithmSpinBox = new QDoubleSpinBox(dockWidget);
    logarithmSpinBox->setRange(0.0, 10.0);
    logarithmSpinBox->setSingleStep(0.1);
    connect(logarithmSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::logarithmImg);

    //Actions
    apply = new QAction("&Apply");
    apply->setIcon(QIcon(":/img/apply.png"));
    connect(apply, &QAction::triggered, this, &MainWindow::applyChanges);

    discard = new QAction("&Discard");
    discard->setIcon(QIcon(":/img/discard.png"));
    connect(discard, &QAction::triggered, this, &MainWindow::discardChanges);

    grayscale = new QAction("&Gray-scale");
    grayscale->setIcon(QIcon(":/img/gray-scale.png"));
    connect(grayscale, &QAction::triggered, this, &MainWindow::grayscaleImg);

    sepia = new QAction("&Sepia");
    sepia->setIcon(QIcon(":/img/sepia.png"));
    connect(sepia, &QAction::triggered, this, &MainWindow::sepiaImg);

    invert = new QAction("&Invert");
    invert->setIcon(QIcon(":/img/invert.png"));
    connect(invert, &QAction::triggered, this, &MainWindow::invertImg);

    pixelize = new QAction("&Pixelize");
    pixelize->setIcon(QIcon(":/img/pixelize.png"));
    connect(pixelize, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Pixelize image");
        cellSize->show();
    });

    twist = new QAction("&Twist");
    twist->setIcon(QIcon(":/img/twist.png"));
    connect(twist, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Twist image");
        twistSlider->show();

    });

    monochrome = new QAction("&Monochrome");
    monochrome->setIcon(QIcon(":/img/monochrome.png"));
    connect(monochrome, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Monochrome image");
        monochromeSlider->show();
        invertMonochrome->show();

    });

    brightness = new QAction("&Brightness");
    brightness->setIcon(QIcon(":/img/brightness.png"));
    connect(brightness, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Image brightness");
        brightnessSlider->show();
    });

    logarithm = new QAction("&Logarithm");
    logarithm->setIcon(QIcon(":/img/logarithm.png"));
    connect(logarithm, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Logarithmic\ntransformation");
        logarithmSpinBox->show();
    });

    binarization = new QAction("&Logarithm");
    binarization->setIcon(QIcon(":/img/binarization.png"));
    connect(binarization, &QAction::triggered, this, [this]()
    {
        hideWidgets();
        title->show();
        title->setText("Image binarization");
        binarizationSlider->show();
        color1Button->show();
        color2Button->show();
    });

    //CheckBox
    invertMonochrome = new QCheckBox("Invert monochrome colors", dockWidget);

    //Buttons
    color1Button = new QPushButton("Color 1", dockWidget);
    color2Button = new QPushButton("Color 2", dockWidget);
    connect(color1Button, &QPushButton::clicked, this, &MainWindow::chooseColor1);
    connect(color2Button, &QPushButton::clicked, this, &MainWindow::chooseColor2);
    color1 = Qt::black; // Черный по умолчанию
    color2 = Qt::white; // Белый по умолчанию

    widgets = {title, cellSize, twistSlider, monochromeSlider, brightnessSlider,
               logarithmSpinBox, invertMonochrome, binarizationSlider, color1Button, color2Button};

    for (QWidget *widget : widgets)
    {
        dockLayout->addWidget(widget);
        widget->hide();
    }

    //Actions for menuBar
    dockLayoutWidget->setLayout(dockLayout);
    dockWidget->setWidget(dockLayoutWidget);

    fileOpen = new QAction("&Open...");
    fileOpen->setIcon(QIcon(":/img/open.png"));
    fileOpen->setShortcut(QKeySequence::Open);
    connect(fileOpen, &QAction::triggered, this, &MainWindow::open);

    fileSave = new QAction("&Save");
    fileSave->setIcon(QIcon(":/img/save.png"));
    fileSave->setShortcut(QKeySequence::Save);
    connect(fileSave, &QAction::triggered, this, &MainWindow::save);
    fileSave->setDisabled(true);

    fileExit = new QAction("&Exit");
    fileExit->setIcon(QIcon(":/img/exit.png"));
    fileExit->setShortcut(QKeySequence::Quit);
    connect(fileExit, &QAction::triggered, this, &MainWindow::close);

    // MenuBar
    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    file = menuBar->addMenu("&File");
    file->addAction(fileOpen);
    file->addAction(fileSave);
    file->addSeparator();
    file->addAction(fileExit);


    // ToolBar
    toolBar = addToolBar("Tools");
    toolBar->hide();

    toolBar->addAction(apply);
    toolBar->addAction(discard);
    toolBar->addSeparator();
    toolBar->addAction(grayscale);
    toolBar->addAction(sepia);
    toolBar->addAction(invert);
    toolBar->addSeparator();
    toolBar->addAction(pixelize);
    toolBar->addAction(twist);
    toolBar->addAction(monochrome);
    toolBar->addAction(brightness);
    toolBar->addSeparator();
    toolBar->addAction(logarithm);
    toolBar->addAction(binarization);
}

void MainWindow::hideWidgets()
{
    for (QWidget *widget : widgets)
        widget->hide();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Image files (*.png *.jpg *.jpeg *.bmp)"));
    QImage imageCopy;
    imageCopy.load(fileName);
    if (imageCopy.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    image = imageCopy;
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);

    toolBar->show();
    dockWidget->show();
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("PNG files (*.png);;JPG files (*.jpg);;JPEG files (*.jpg);;BMP files (*.bmp)"));
    if (image.isNull())
    {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot save %1").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    else
        image.save(fileName);
}

void MainWindow::close()
{
    if (QMessageBox::question(this, "Exit Dialog", "Do you really want to exit?") == QMessageBox::StandardButton::Yes)
        QApplication::quit();
}

void MainWindow::applyChanges()
{
    image = imgCopy;
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
    fileSave->setEnabled(true);
}

void MainWindow::discardChanges()
{
    imgCopy = image.copy(image.rect());
    drawImage();
}

void MainWindow::drawImage()
{
    pixmap = QPixmap::fromImage(imgCopy);
    label->setPixmap(pixmap);
}

void MainWindow::grayscaleImg()
{
    imgCopy = image.copy(image.rect()).convertToFormat(QImage::Format_Grayscale8);
    imgCopy = imgCopy.convertToFormat(QImage::Format_Grayscale8);
    drawImage();
}

void MainWindow::sepiaImg()
{
    imgCopy = image.copy(image.rect());

    for(int y = 0; y < imgCopy.height(); y++)
        for(int x = 0; x < imgCopy.width(); x++)
        {
            QRgb pixelColor = imgCopy.pixel(x, y);

            int oldRed = qRed(pixelColor);
            int oldGreen = qGreen(pixelColor);
            int oldBlue = qBlue(pixelColor);

            int newRed = qBound(0, (int)(0.393 * oldRed + 0.769 * oldGreen + 0.189 * oldBlue), 255);
            int newGreen = qBound(0, (int)(0.349 * oldRed + 0.686 * oldGreen + 0.168 * oldBlue), 255);
            int newBlue = qBound(0, (int)(0.272 * oldRed + 0.534 * oldGreen + 0.131 * oldBlue), 255);

            imgCopy.setPixel(x, y, qRgb(newRed, newGreen, newBlue));
        }

    drawImage();
}

void MainWindow::invertImg()
{
    imgCopy = image.copy(image.rect());

    for (int y = 0; y < imgCopy.height(); y++)
        for (int x = 0; x < imgCopy.width(); x++)
        {
            QRgb pixelColor = imgCopy.pixel(x, y);

            int red = 255 - qRed(pixelColor);
            int green = 255 - qGreen(pixelColor);
            int blue = 255 - qBlue(pixelColor);

            imgCopy.setPixel(x, y, qRgb(red, green, blue));
        }

    drawImage();
}

void MainWindow::pixelizeImg()
{
    imgCopy = image.copy(image.rect());
    const int CELL_SIZE = cellSize->value();

    for (int y = 0; y < imgCopy.height(); y += CELL_SIZE)
        for (int x = 0; x < imgCopy.width(); x += CELL_SIZE)
        {
            QRgb pixelColor = imgCopy.pixel(x, y);
            for (int dy = 0; dy < CELL_SIZE; dy++)
                for (int dx = 0; dx < CELL_SIZE; dx++)
                {
                    int newY = y + dy;
                    int newX = x + dx;

                    if (newY < imgCopy.height() && newX < imgCopy.width())
                        imgCopy.setPixel(newX, newY, pixelColor);
                }
        }

    drawImage();
}

void MainWindow::twistImg()
{
    imgCopy = image.copy(image.rect());

    float maxAngle = (twistSlider->value() * M_PI) / 180;
    float maxDistance = QVector2D(imgCopy.width(), imgCopy.height()).length() / 2;

    QVector2D imageCenter(imgCopy.width() / 2, imgCopy.height() / 2);

    for(int i = 0; i < imgCopy.height(); i++)
        for(int j = 0; j < imgCopy.width(); j++)
        {
            QVector2D currentPos(j, i);
            QVector2D v = currentPos - imageCenter;
            float r = v.length();
            float twirlAngle = r / maxDistance * maxAngle;
            float angle = atan2(v.y(), v.x());
            QVector2D out(r * cos(angle+twirlAngle) + imageCenter.x(), r * sin(angle+twirlAngle)+imageCenter.y());
            int x = out.x();
            int y = out.y();
            if (x < 0)
                x = 0;

            if (x > imgCopy.width()-1)
                x = imgCopy.width()-1;

            if (y < 0)
                y = 0;

            if (y > imgCopy.height()-1)
                y = imgCopy.height()-1;

            imgCopy.setPixel(j, i, image.pixel(x, y));
        }

    drawImage();
}

void MainWindow::monochromeImg()
{
    imgCopy = image.copy(image.rect());

    if (invertMonochrome->isChecked())
        imgCopy.invertPixels();

    int value = monochromeSlider->value();
    imgCopy = imgCopy.convertToFormat(QImage::Format_Mono, Qt::ThresholdDither | Qt::AvoidDither);

    switch (value)
    {
    case 0:
        imgCopy.setColor(0, qRgb(255, 0, 0));
        break;
    case 1:
        imgCopy.setColor(0, qRgb(0, 255, 0));
        break;
    case 2:
        imgCopy.setColor(0, qRgb(0, 0, 255));
        break;
    }

    drawImage();
}

void MainWindow::brightnessImg()
{
    imgCopy = image.copy(image.rect());
    int brightness = brightnessSlider->value();

    int pixels = imgCopy.width() * imgCopy.height();
    unsigned int *data = (unsigned int *)imgCopy.bits();

    for (int i = 0; i < pixels; ++i)
    {
        int r = qRed(data[i]) + brightness;
        int g = qGreen(data[i]) + brightness;
        int b = qBlue(data[i]) + brightness;

        r = (r > 255) ? 255 : ((r < 0) ? 0 : r);
        g = (g > 255) ? 255 : ((g < 0) ? 0 : g);
        b = (b > 255) ? 255 : ((b < 0) ? 0 : b);

        data[i] = qRgb(r, g, b);
    }
    drawImage();
}

void MainWindow::logarithmImg()
{
    imgCopy = image.copy(image.rect());
    double constant = logarithmSpinBox->value();

    for (int y = 0; y < imgCopy.height(); y++)
        for (int x = 0; x < imgCopy.width(); x++)
        {
            QRgb pixelColor = imgCopy.pixel(x, y);

            int red = qBound(0, int(qRed(pixelColor) * constant), 255);
            int green = qBound(0, int(qGreen(pixelColor) * constant), 255);
            int blue = qBound(0, int(qBlue(pixelColor) * constant), 255);

            imgCopy.setPixel(x, y, qRgb(red, green, blue));
        }

    drawImage();
}

void MainWindow::chooseColor1()
{
    QColor selectedColor = QColorDialog::getColor(color1, this, "Выберите цвет C1");
    if (selectedColor.isValid())
    {
        color1 = selectedColor;
        binarizationImg();
    }
}

void MainWindow::chooseColor2()
{
    QColor selectedColor = QColorDialog::getColor(color2, this, "Выберите цвет C2");
    if (selectedColor.isValid())
    {
        color2 = selectedColor;
        binarizationImg();
    }
}

void MainWindow::binarizationImg()
{
    imgCopy = image.copy(image.rect());
    int threshold = binarizationSlider->value();

    for(int y = 0; y < imgCopy.height(); y++)
        for(int x = 0; x < imgCopy.width(); x++)
        {
            QRgb pixelColor = imgCopy.pixel(x, y);

            int averageBrightness = (qRed(pixelColor) + qGreen(pixelColor) + qBlue(pixelColor)) / 3;

            QColor newColor = (averageBrightness <= threshold) ? color1 : color2;
            imgCopy.setPixel(x, y, newColor.rgb());
        }

    drawImage();
}

MainWindow::~MainWindow()
{
}

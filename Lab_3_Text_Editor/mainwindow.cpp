#include "mainwindow.h"
#include "qapplication.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Text Editor v.1.0");
    this->setWindowIcon(QIcon(":/img/icon.png"));


    //File Menu
    fileNew = new QAction("&New...");
    fileNew->setIcon(QIcon(":/img/new.png"));
    fileNew->setShortcut(QKeySequence::New);
    connect(fileNew, &QAction::triggered, this, &MainWindow::newFile);

    fileOpen = new QAction("&Open...");
    fileOpen->setIcon(QIcon(":/img/open.png"));
    fileOpen->setShortcut(QKeySequence::Open);
    connect(fileOpen, &QAction::triggered, this, &MainWindow::open);


    fileSave = new QAction("&Save");
    fileSave->setIcon(QIcon(":/img/save.png"));
    fileSave->setShortcut(QKeySequence::Save);
    connect(fileSave, &QAction::triggered, this, &MainWindow::save);

    fileSaveAs = new QAction("&Save As...");
    fileSaveAs->setShortcut(QKeySequence::SaveAs);
    connect(fileSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

    fileExit = new QAction("&Exit");
    fileExit->setIcon(QIcon(":/img/exit.png"));
    fileExit->setShortcut(QKeySequence::Quit);
    connect(fileExit, &QAction::triggered, this, &MainWindow::close);


    //Edit Menu
    cleanTextField = new QAction("&Clean text field");
    cleanTextField->setIcon(QIcon(":/img/clear.png"));
    connect(cleanTextField, &QAction::triggered, this, [this]() {editor->clear();});

    enlarge = new QAction("&Enlarge the font");
    enlarge->setIcon(QIcon(":/img/enlarge.png"));
    connect(enlarge, &QAction::triggered, this, [this]() {changeTextSize(2);});

    shrink = new QAction("&Shrink the font");
    shrink->setIcon(QIcon(":/img/shrink.png"));
    connect(shrink, &QAction::triggered, this, [this]() {changeTextSize(-2);});

    uppercase = new QAction("&In uppercase");
    uppercase->setIcon(QIcon(":/img/uppercase.png"));
    connect(uppercase, &QAction::triggered, this, [this]() {changeTextCase(true);});

    lowercase = new QAction("&In lowercase");
    lowercase->setIcon(QIcon(":/img/lowercase.png"));
    connect(lowercase, &QAction::triggered, this, [this]() {changeTextCase(false);});

    replace = new QAction("&Replace last occurrence");
    replace->setIcon(QIcon(":/img/replace.png"));
    connect(replace, &QAction::triggered, this, &MainWindow::replaceLastOccurrence);


    //Help Menu
    reference = new QAction("&Reference");
    reference->setIcon(QIcon(":/img/reference.png"));
    connect(reference, &QAction::triggered, this, &MainWindow::showHelp);

    about = new QAction("&About...");
    about->setIcon(QIcon(":/img/about.png"));
    connect(about, &QAction::triggered, this, &MainWindow::showAboutDialog);


    //MenuBar
    appMenuBar = new QMenuBar(this);
    file = appMenuBar->addMenu("&File");
    edit = appMenuBar->addMenu("&Edit");
    help = appMenuBar->addMenu("&Help");
    this->setMenuBar(appMenuBar);

    file->addAction(fileNew);
    file->addAction(fileOpen);
    file->addSeparator();
    file->addAction(fileSave);
    file->addAction(fileSaveAs);
    file->addSeparator();
    file->addAction(fileExit);

    edit->addAction(cleanTextField);
    edit->addSeparator();
    edit->addAction(uppercase);
    edit->addAction(lowercase);
    edit->addSeparator();
    edit->addAction(enlarge);
    edit->addAction(shrink);
    edit->addSeparator();
    edit->addAction(replace);

    help->addAction(reference);
    help->addSeparator();
    help->addAction(about);


    //ToolBar
    tools = addToolBar("Tools");
    tools->addAction(cleanTextField);
    tools->addSeparator();
    tools->addAction(uppercase);
    tools->addAction(lowercase);
    tools->addSeparator();
    tools->addAction(enlarge);
    tools->addAction(shrink);
    tools->addSeparator();
    tools->addAction(replace);


    //Status Bar
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);


    //Text Edit and filename Label
    filenameLabel = new QLabel(this);
    editor = new QTextEdit();
    editor->setReadOnly(true);

    layout = new QVBoxLayout();
    layout->addWidget(filenameLabel);
    layout->addWidget(editor);

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);


    //ToolButtons for dockWidgets
    fileLayout = new QHBoxLayout();
    createToolButton(":/img/new.png", fileNew, true);
    createToolButton(":/img/open.png", fileOpen, true);
    createToolButton(":/img/save.png", fileSave, true);
    createToolButton(":/img/exit.png", fileExit, true);

    editLayout = new QGridLayout();
    for(int i = 0; i < 3; i++)
        editLayout->setColumnStretch(i, 1);

    createToolButton(":/img/uppercase.png", uppercase, false);
    createToolButton(":/img/lowercase.png", lowercase, false);
    createToolButton(":/img/clear.png", cleanTextField, false);
    createToolButton(":/img/enlarge.png", enlarge, false);
    createToolButton(":/img/shrink.png", shrink, false);
    createToolButton(":/img/replace.png", replace, false);


    //DockWidgets
    dockFile = new QDockWidget("File", this);
    dockFile->setAllowedAreas(Qt::TopDockWidgetArea);
    dockFile->setFixedSize(QSize(250 , 85));
    dockFileWidget = new QWidget(dockFile);
    dockFileWidget->setLayout(fileLayout);
    dockFile->setWidget(dockFileWidget);

    dockEdit = new QDockWidget("Edit", this);
    dockEdit->setAllowedAreas(Qt::RightDockWidgetArea);
    dockEdit->setFixedSize(QSize(200, 150));
    dockEditWidget = new QWidget(dockEdit);
    dockEditWidget->setLayout(editLayout);
    dockEdit->setWidget(dockEditWidget);

    this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    this->addDockWidget(Qt::TopDockWidgetArea, dockFile);
    this->addDockWidget(Qt::RightDockWidgetArea, dockEdit);

    this->showMaximized();
}

void MainWindow::createToolButton(const QString &iconPath, QAction *action, bool isFileToolButton)
{
    QToolButton *button = new QToolButton(this);
    button->setIcon(QIcon(iconPath));
    button->setFixedSize(50, 50);
    if(isFileToolButton)
        fileLayout->addWidget(button);
    else
        editLayout->addWidget(button);

    connect(button, &QToolButton::clicked, action, &QAction::trigger);
}

void MainWindow::newFile()
{
    editor->setReadOnly(false);
    fileSave->setEnabled(false);
    filenameLabel->setText("new.txt");
    statusBar->showMessage("New file created successfully.");
}

void MainWindow::open()
{
    disconnect(editor, &QTextEdit::textChanged, this, &MainWindow::textChanged);
    editor->setReadOnly(false);
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Text files (*.txt)"));
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this , tr("Error"), tr("Cannot open file"));
            return ;
        }
        QTextStream inputStream(&file);
        QString txt = inputStream.readAll();
        editor->setText(txt);

        QFileInfo fileInfo(filePath);
        filenameLabel->setText(fileInfo.fileName());
        connect(editor, &QTextEdit::textChanged, this, &MainWindow::textChanged);
        file.close();
    }
}

void MainWindow::save()
{
    QFile file(filePath);
    qDebug() << filePath;
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outputStream(&file);
        outputStream << editor->toPlainText();
        outputStream.flush();
        file.close();
    }
    else
        QMessageBox::critical(this, tr("Error"), tr("Cannot save file"));

    unsavedChanges = false;
    updateFilenameLabel();
    statusBar->showMessage("File saved successfully.");
}

void MainWindow::saveAs()
{   
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString("new.txt"), tr("Text files (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Cannot open file"));
            return;
        }
        else
        {
            QTextStream outputStream(&file);
            outputStream << editor->toPlainText();
            outputStream.flush();
            file.close();
        }
    }
    fileSave->setEnabled(true);
    unsavedChanges = false;
    updateFilenameLabel();
    statusBar->showMessage("File saved successfully.");
}

void MainWindow::close()
{
    if (QMessageBox::question(this, "Exit Dialog", "Do you really want to exit?") == QMessageBox::StandardButton::Yes)
        QApplication::quit();
}

void MainWindow::textChanged()
{
    unsavedChanges = true;
    updateFilenameLabel();
}

void MainWindow::updateFilenameLabel()
{
    QString filename = filenameLabel->text();
    if (unsavedChanges && !symbolAdded)
    {
        filename += " *";
        symbolAdded = true;
        qDebug() << filename;

    }
    qDebug() << filename;
    if (!unsavedChanges && symbolAdded)
    {
        filename.chop(2);
        symbolAdded = false;
        qDebug() << filename;
    }

    qDebug() << filename;
    filenameLabel->setText(filename);
}

void MainWindow::changeTextSize(int delta)
{
    QTextCursor cursor = editor->textCursor();
    if (!cursor.hasSelection())
        return;

    QFont font = cursor.charFormat().font();
    int currentSize = font.pointSize();
    font.setPointSize(currentSize + delta);

    QTextCharFormat format;
    format.setFont(font);

    cursor.mergeCharFormat(format);
}

void MainWindow::changeTextCase(bool toUpper)
{
    QTextCursor cursor = editor->textCursor();
    QString selectedText = cursor.selectedText();
    if (!selectedText.isEmpty())
    {
        if (toUpper)
            selectedText = selectedText.toUpper();
        else
            selectedText = selectedText.toLower();

        cursor.insertText(selectedText);
    }
}

void MainWindow::replaceLastOccurrence()
{
    QString searchText = QInputDialog::getText(nullptr, "Replace Text", "Find text:");
    if (searchText.isEmpty())
        return;

    QString replaceText = QInputDialog::getText(nullptr, "Replace Text", "Replace with:");

    QTextCursor cursor = editor->textCursor();
    QString text = editor->toPlainText();

    int lastPos = text.lastIndexOf(searchText);

    if (lastPos != -1)
    {
        cursor.setPosition(lastPos + searchText.length());
        cursor.setPosition(lastPos, QTextCursor::KeepAnchor);
        cursor.insertText(replaceText);
    }

    editor->setTextCursor(cursor);
}

void MainWindow::showAboutDialog()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About...");
    aboutBox.setText("Text Editor v1.0\n\nThis is a simple text editor written in Qt.");
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setWindowIcon(QIcon(":/img/about.png"));
    aboutBox.exec();
}

void MainWindow::showHelp()
{
    QDialog helpDialog(this);
    helpDialog.setWindowTitle("Help");

    QTextEdit *helpText = new QTextEdit(&helpDialog);
    helpText->setPlainText("How to use this simple text editor?\n"
                           "The File menu and File dockwidget allows you to create a new file, open an existing file, "
                           "save changes, save changes to another file and close the program.\n"
                           "In the Edit menu as well as in the Edit dockwidget and toolbar you can clear the text field, "
                           "set the selected text to upper/lower case and increase/decrease the selected text. "
                           "You can also replace the last occurrence of a word/symbol with another word/symbol.");
    helpText->setReadOnly(true);

    QPushButton *closeButton = new QPushButton("Close", &helpDialog);
    connect(closeButton, &QPushButton::clicked, &helpDialog, &QDialog::close);

    QVBoxLayout *layout = new QVBoxLayout(&helpDialog);
    layout->addWidget(helpText);
    layout->addWidget(closeButton);

    helpDialog.exec();
}

MainWindow::~MainWindow()
{
}


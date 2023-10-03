#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QDockWidget>
#include <QTextEdit>
#include <QLabel>
#include <QStatusBar>
#include <QToolButton>

#include <QMessageBox>
#include <QFileDialog>

#include <QWidget>
#include<QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include<QInputDialog>

#include <QPushButton>


#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *tools;
    QMenuBar *appMenuBar;
    QMenu *file, *edit, *help;

    QAction *fileNew, *fileOpen , *fileSave, *fileSaveAs, *fileExit;
    QAction *cleanTextField, *uppercase, *lowercase, *enlarge, *shrink, *replace;
    QAction *about, *reference;

    QDockWidget *dockEdit, *dockFile;
    QTextEdit *editor;

    QLabel *filenameLabel;

    QStatusBar *statusBar;

    QToolButton *newButton, *openButton, *saveButton, *saveAsButton;


    QWidget *dockEditWidget, *dockFileWidget;



    QGridLayout *editLayout;
    QVBoxLayout *layout;
    QHBoxLayout *fileLayout;

    QString filePath;


    void createToolButton(const QString &iconPath, QAction *action, bool isFileToolButton);

    bool unsavedChanges = false, symbolAdded = false;

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void close();

    void textChanged();
    void updateFilenameLabel();

    void changeTextSize(int delta);
    void changeTextCase(bool toUpper);

    void replaceLastOccurrence();

    void showAboutDialog();

    void showHelp();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

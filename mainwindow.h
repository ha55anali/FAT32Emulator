#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inputsize.h"
#include <qdynamicbutton.h>

#include "coreProgram/fileSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fileProp(QString name,QString content);

public slots:

private slots:
    void on_addFile_clicked();
    void SlotGetNumber();// SLOT for getting number of the dynamic buttons


    void getSizeInput(int size,int no);
    void deleteFileBut(std::string name);

private:
    Ui::MainWindow *ui;

    void createFileSystem();

    int sectorSize;
    int NoSectors;

    fileSystem* Fs;
    std::string temp;
};
#endif // MAINWINDOW_H

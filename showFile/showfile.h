#ifndef SHOWFILE_H
#define SHOWFILE_H

#include <QDialog>
#include "coreProgram/fileSystem.h"

class MainWindow;

namespace Ui {
class ShowFile;
}

class ShowFile : public QDialog
{
    Q_OBJECT

public:
    explicit ShowFile(fileSystem* F,std::string nam,MainWindow* m,QWidget *parent = nullptr);
    ~ShowFile();

private slots:
    void on_delete_2_clicked();

signals:
    void deleteFile(std::string name);

private:
    Ui::ShowFile *ui;
    fileSystem * Fs;
    std::string name;
    MainWindow* main;
};

#endif // SHOWFILE_H

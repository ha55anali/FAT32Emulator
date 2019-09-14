#ifndef CREATEFILE_H
#define CREATEFILE_H

#include <QDialog>

class MainWindow;

namespace Ui {
class createFile;
}

class createFile : public QDialog
{
    Q_OBJECT

public:
    explicit createFile(MainWindow* m,QWidget *parent = nullptr);
    ~createFile();

private slots:
    void on_confirm_clicked();

    void on_cancel_clicked();

private:
    Ui::createFile *ui;

    MainWindow* main;
};

#endif // CREATEFILE_H

#ifndef INPUTSIZE_H
#define INPUTSIZE_H

#include <QDialog>
class MainWindow;

namespace Ui {
class inputSize;
}

class inputSize : public QDialog
{
    Q_OBJECT

public:
    explicit inputSize(MainWindow* m, QWidget *parent = nullptr);
    ~inputSize();

private slots:
    void on_pushButton_clicked();

signals:
    void sendSizeValues(int size,int no);

private:
    Ui::inputSize *ui;
    MainWindow* main;
};

#endif // INPUTSIZE_H

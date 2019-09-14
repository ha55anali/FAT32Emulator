#include "inputsize.h"
#include "ui_inputsize.h"
#include "mainwindow.h"

#include<QMessageBox>

inputSize::inputSize(MainWindow* m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputSize)
{

    main=m;
    ui->setupUi(this);
}

inputSize::~inputSize()
{
    delete ui;

}

void inputSize::on_pushButton_clicked()
{
    int sizeSector=ui->SizeSector->text().toInt();
    int noOfSectors=ui->NoSectors->text().toInt();

    if (!(sizeSector>0 && noOfSectors>0)){
        QMessageBox msgBox;
        msgBox.setText("Enter valid values.");
        msgBox.exec();
    }
    else{
        emit sendSizeValues(sizeSector,noOfSectors);

        this->close();
    }
}

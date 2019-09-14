#include "createfile.h"
#include "ui_createfile.h"

#include "mainwindow.h"
#include <QMessageBox>

createFile::createFile(MainWindow * m,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createFile)
{
    ui->setupUi(this);
    main=m;
}

createFile::~createFile()
{
    delete ui;
}

void createFile::on_confirm_clicked()
{
    try{
        main->fileProp(ui->name->text(),ui->content->text());
        this->close();
    }
    catch(std::invalid_argument& e){
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

}

void createFile::on_cancel_clicked()
{
    this->close();
}

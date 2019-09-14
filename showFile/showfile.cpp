#include "showfile.h"
#include "ui_showfile.h"
#include "mainwindow.h"

ShowFile::ShowFile(fileSystem* F,std::string nam,MainWindow* m,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowFile)
{
    ui->setupUi(this);
    Fs=F;
    name=nam;
    main=m;

    ui->name->setText(QString::fromStdString(name));
    ui->content->setText(QString::fromStdString(Fs->readFile(name)));
}


ShowFile::~ShowFile()
{
    delete ui;
}

void ShowFile::on_delete_2_clicked()
{
    connect(this,SIGNAL(deleteFile(std::string)),main,SLOT(deleteFileBut(std::string)));
    Fs->deleteFile(name);
    emit deleteFile(name);
    this->close();
}

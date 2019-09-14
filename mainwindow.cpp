#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "showFile/showfile.h"
#include "CreateFile/createfile.h"

#include <qsizepolicy.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    createFileSystem();

}

void MainWindow::createFileSystem(){


    inputSize input(this);
    connect(&input,SIGNAL(sendSizeValues(int,int))
            ,this,SLOT(getSizeInput(int,int)));
    input.setModal(true);
    input.exec();
    ui->setupUi(this);

    disconnect(&input,SIGNAL(sendSizeValues(int,int))
            ,this,SLOT(getSizeInput(int,int)));

    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->horizontalLayoutWidget);
    ui->horizontalLayoutWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    Fs=new fileSystem(NoSectors,sectorSize);

    connect(ui->addFile, &QPushButton::clicked, this, &MainWindow::on_addFile_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Fs;
}

void MainWindow::fileProp(QString name,QString content){
    Fs->saveFile(name.toStdString(),content.toStdString(),content.toStdString().size());
    temp=name.toStdString();
}

void MainWindow::getSizeInput(int size,int no){
    NoSectors=no;
    sectorSize=size;
}


void MainWindow::on_addFile_clicked()
{
    createFile create(this);
    create.setModal(true);
    create.exec();

    QDynamicButton *button = new QDynamicButton(temp,this);  // Create a dynamic button object
    button->setText("File " + QString::number(button->getID())+"\nname: "+QString::fromStdString(temp));
    connect(button, SIGNAL(clicked()), this, SLOT(SlotGetNumber()));
    ui->horizontalLayout_2->addWidget(button);
}


void MainWindow::SlotGetNumber()
{
    /* To determine the object that caused the signal
     * */
    QDynamicButton *button = (QDynamicButton*) sender();
    /* Then set the number of buttons in lineEdit,
     * which is contained in the dynamic button
     * */


    ShowFile showFile(Fs,button->getName(),this);
    showFile.setModal(true);
    showFile.exec();
    /* That is the key number is set to lineEdit field only
     * when we press one of the dynamic keys,
     * and this number corresponds to the button you pressed
     * */
}

void MainWindow::deleteFileBut(std::string name){
    /* Iterates through all elements of the layer, where are dynamic buttons
     * */
    for(int i = 0; i < ui->horizontalLayout_2->count(); i++){
        /* We produce cast layer element in the dynamic button object
         * */
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->horizontalLayout_2->itemAt(i)->widget());
        /* If the button number corresponds to the number that is set to lineEdit,
         * then deletes the button
         * */
        if(button->getName() == name){
            button->hide();
            delete button;
        }
    }
}

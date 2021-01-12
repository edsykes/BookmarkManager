#include "newfolder.h"
#include "ui_newfolder.h"

NewFolder::NewFolder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFolder)
{
    ui->setupUi(this);
}

NewFolder::~NewFolder()
{
    delete ui;
}

QString NewFolder::getFolderName()
{
    return folderName;
}

void NewFolder::on_lineEdit_editingFinished()
{
    folderName =  ui->lineEdit->text();
}

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

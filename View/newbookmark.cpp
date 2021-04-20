#include "newbookmark.h"
#include "ui_newbookmark.h"

NewBookmark::NewBookmark(QStringList browsers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBookmark)
{
    ui->setupUi(this);
    ui->browserCombo->insertItems(0,browsers);
}

NewBookmark::~NewBookmark()
{
    delete ui;
}

QString NewBookmark::getBrowser()
{
    return ui->browserCombo->currentText();
}

QString NewBookmark::getName()
{
    return bookmarkName;
}

QString NewBookmark::getUrl()
{
    return url;
}

void NewBookmark::on_editBoxName_editingFinished()
{
    bookmarkName = ui->editBoxName->text();
}

void NewBookmark::on_editBoxUrl_editingFinished()
{
    url = ui->editBoxUrl->text();
}

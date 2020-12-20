#include "newbookmark.h"
#include "ui_newbookmark.h"

NewBookmark::NewBookmark(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBookmark)
{
    ui->setupUi(this);
}

NewBookmark::~NewBookmark()
{
    delete ui;
}

QString NewBookmark::getBrowser()
{
    return browser;
}

void NewBookmark::on_editBrowser_editingFinished()
{
    browser = ui->editBrowser->text();
}

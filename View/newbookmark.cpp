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

QString NewBookmark::getName()
{
    return bookmarkName;
}

QString NewBookmark::getUrl()
{
    return url;
}

void NewBookmark::on_editBrowser_editingFinished()
{
    browser = ui->editBrowser->text();

}

void NewBookmark::on_editBoxName_editingFinished()
{
    bookmarkName = ui->editBoxName->text();
}

void NewBookmark::on_editBoxUrl_editingFinished()
{
    url = ui->editBoxUrl->text();
}

#ifndef NEWBOOKMARK_H
#define NEWBOOKMARK_H

#include <QDialog>

namespace Ui {
class NewBookmark;
}

class NewBookmark : public QDialog
{
    Q_OBJECT

public:
    explicit NewBookmark(QWidget *parent = nullptr);
    ~NewBookmark();
    QString getBrowser();

private slots:
    void on_editBrowser_editingFinished();

private:
    Ui::NewBookmark *ui;
    QString browser;
};

#endif // NEWBOOKMARK_H

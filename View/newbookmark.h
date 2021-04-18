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
    explicit NewBookmark(QStringList browsers, QWidget *parent = nullptr);
    ~NewBookmark();
    QString getBrowser();    
    QString getUrl();
    QString getName();
private slots:
    void on_editBrowser_editingFinished();
    void on_editBoxName_editingFinished();
    void on_editBoxUrl_editingFinished();
private:
    Ui::NewBookmark *ui;
    QString browser;
    QString bookmarkName;
    QString url;
};
#endif // NEWBOOKMARK_H

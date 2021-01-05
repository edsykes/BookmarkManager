#ifndef NEWFOLDER_H
#define NEWFOLDER_H

#include <QDialog>

namespace Ui {
class NewFolder;
}

class NewFolder : public QDialog
{
    Q_OBJECT

public:
    explicit NewFolder(QWidget *parent = nullptr);
    ~NewFolder();

    QString getFolderName();

private slots:
    void on_lineEdit_editingFinished();

private:
    Ui::NewFolder *ui;
    QString folderName;
};

#endif // NEWFOLDER_H

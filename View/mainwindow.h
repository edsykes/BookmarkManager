#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

class QDir;
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTreeView();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void on_pushButton_clicked();
    void onPopupMenuClicked();
    void on_pushStartChrome_clicked();
    void on_startEdge_clicked();
    void on_dockChromeRight_clicked();
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_buttonAddBookmark_clicked();

    void DockLeft();
    
    void on_pushDockLeft_clicked();

private:
    void launchChromeUrl(QString url);
    QString readJsonFile(QString path);
    Ui::MainWindow *ui;
    QMenu *contextMenu;
    QAction *popupAction;
    QDir* bookmarkDirectory;

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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

private:
    Ui::MainWindow *ui;
    QMenu *contextMenu;
    QAction *popupAction;
};
#endif // MAINWINDOW_H

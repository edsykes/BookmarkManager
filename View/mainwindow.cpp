#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QContextMenuEvent>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <Windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    popupAction = new QAction("pop up");
    connect(popupAction, &QAction::triggered, this, &MainWindow::onPopupMenuClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTreeView(){
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath("c:\\users");
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->setRootPath("c:\\users"));
    ui->bookmarkDirectory->setText(model->rootPath());
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    QFileSystemModel* model = (QFileSystemModel*)ui->treeView->model();
    int row = -1;
    foreach (QModelIndex index, list)
    {
        if (index.row()!=row && index.column()==0)
        {
            QFileInfo fileInfo = model->fileInfo(index);
            qDebug() << fileInfo.fileName() << '\n';
            qDebug() << fileInfo.filePath() << '\n';
            row = index.row();
        }
    }
    QMenu menu(this);
    menu.addAction(popupAction);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::onPopupMenuClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Menu was clicked");
    msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    QFileSystemModel* model = (QFileSystemModel*)ui->treeView->model();
    int row = -1;
    QModelIndex selectedIndex;
    foreach (QModelIndex index, list)
    {
        if (index.row()!=row && index.column()==0)
        {
            selectedIndex = index;
            row = index.row();
        }
    }

    QFileInfo fileInfo = model->fileInfo(selectedIndex);
    qDebug() << fileInfo.fileName() << '\n';
    qDebug() << fileInfo.filePath() << '\n';
}

void MainWindow::on_pushStartChrome_clicked()
{
    QString program("C:/Program Files (x86)/Google/Chrome/Application/chrome.exe");
    QStringList arguments;
    arguments << "www.bing.com";
    arguments << "-window-size=\"400,300\"";
    arguments << "-window-position=\"0,0\"";
    QProcess::startDetached(program, arguments);
}

void MainWindow::on_startEdge_clicked()
{
    QString program("C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe");
    QStringList arguments;
    arguments << "http://www.bing.com";
    QProcess::startDetached(program, arguments);

}

HWND foundHwnd;

BOOL CALLBACK WorkerProc(HWND hwnd, LPARAM) {
    int length = GetWindowTextLength(hwnd);
    TCHAR* buffer = new TCHAR[length + 1];

    GetWindowText(hwnd, buffer, length + 1);
    qDebug() << buffer;
    QString qBuffer = QString::fromWCharArray(buffer);
    if(qBuffer.contains("Chrome")) {
        // do something with hwnd here
        foundHwnd = hwnd;
        return FALSE;
    }

    return TRUE;
}


void MainWindow::on_dockChromeRight_clicked()
{
    //HWND chromeHwn = FindWindow(L"Chrome_WidgetWin_1", L"Google - Google Chrome");
    HWND chromeHwn = 0;
    LPARAM params = 0;
    EnumWindows(WorkerProc, params);
    chromeHwn = foundHwnd;
    qDebug() << "chrome resize clicked " << chromeHwn;
    //SetWindowPos(chromeHwn, nullptr, 200, 0, 1000, 800, SWP_NOZORDER);
    WINBOOL result = SetWindowPos(chromeHwn, NULL, 200, 100, 500, 500, SWP_NOZORDER | SWP_NOACTIVATE);
    qDebug() << "SetWindowPos result" << result;
}


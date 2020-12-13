#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QContextMenuEvent>
#include <QFileSystemModel>
#include <QMessageBox>

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
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath("c:\\users");
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->setRootPath("c:\\users"));
    ui->bookmarkDirectory->setText(model->rootPath());
}


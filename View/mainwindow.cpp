#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newbookmark.h"
#include "newfolder.h"
#include "bookmarkiconprovider.h"
#include "favicondownloader.h"
#include <QContextMenuEvent>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <Windows.h>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <utility>
#include <QDesktopWidget>
#include <QScreen>
#include <QThread>
#include <QAction>
#include <QMenu>
#include <QNetworkAccessManager>

QRect MainWindow::GetCurrentScreenGeometry()
{
    int currentWidth = this->width();
    int topOfWindow = 0;
    int middleWidth = currentWidth / 2;
    QPoint middleOfTopOfWindow = {middleWidth, topOfWindow};
    QPoint globalPosition = mapToGlobal(middleOfTopOfWindow);
    QScreen* currentScreen = QGuiApplication::screenAt(globalPosition);

    // 2. Get the geometry of that screen
    QRect currentScreenGeometry = currentScreen->availableGeometry();

    return currentScreenGeometry;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    popupAction = new QAction("pop up");
    connect(popupAction, &QAction::triggered, this, &MainWindow::onPopupMenuClicked);

    bookmarkDirectory = new QDir("C:/Users/edsyk/OneDrive/Bookmarks");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTreeView(){
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(bookmarkDirectory->path());
    BookmarkIconProvider* bookmarkIcons = new BookmarkIconProvider();
    model->setIconProvider(bookmarkIcons);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->setRootPath(bookmarkDirectory->path()));
    //ui->bookmarkDirectory->setText(model->rootPath());
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    for (int i = 1; i < model->columnCount(); ++i)
        ui->treeView->hideColumn(i);
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

QFileInfo MainWindow::GetSelectedBookmark()
{
    QModelIndexList list = ui->treeView->selectionModel()->selectedIndexes();
    if(list.empty())
    {
        return QFileInfo(bookmarkDirectory->path());
    }

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

    return fileInfo;
}

void MainWindow::on_pushButton_clicked()
{
    QFileInfo fileInfo = GetSelectedBookmark();
    qDebug() << fileInfo.fileName() << '\n';
    qDebug() << fileInfo.filePath() << '\n';
}

void MainWindow::on_pushStartChrome_clicked()
{
    launchChromeUrl("www.bing.com");
}

void MainWindow::on_startEdge_clicked()
{
    QString program("C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe");
    QStringList arguments;
    arguments << "http://www.bing.com";
    QProcess::startDetached(program, arguments);

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    qDebug() << index.column();
    QFileSystemModel* model = (QFileSystemModel*)ui->treeView->model();
    QString clickedFile = model->filePath(index);
    qDebug() << clickedFile;
    QString bookmarkJson = readJsonFile(clickedFile);
    if(bookmarkJson.size() == 0) return;

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(bookmarkJson.toUtf8(), &parseError);
    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "Error while parsing Json";
        return;
    }

    qDebug() << "url:" << jsonDocument["url"];
    qDebug() << "version:" << jsonDocument["version"];
    qDebug() << "browser:" << jsonDocument["browser"];

    if(jsonDocument["browser"] == "chrome")
    {
        qDebug() << "Launching chrome";
        launchChromeUrl(jsonDocument["url"].toString());
    }
    else if(jsonDocument["browser"] == "brave")
    {
        qDebug() << "Launching brave";
        launchBraveUrl(jsonDocument["url"].toString());
    }
    else if(jsonDocument["browser"] == "ie")
    {
        qDebug() << "Launching IE";
        launchIEUrl(jsonDocument["url"].toString());
    }
}

void MainWindow::launchChromeUrl(QString url)
{
    QString program("C:/Program Files (x86)/Google/Chrome/Application/chrome.exe");
    QStringList arguments;
    arguments << url;
    arguments << "-window-size=\"400,300\"";
    arguments << "-window-position=\"0,0\"";
    QProcess::startDetached(program, arguments);
}

QString MainWindow::readJsonFile(QString path)
{
    QFile jsonFile(path);
    if(!jsonFile.open(QFile::ReadOnly| QFile::Text))
    {
        qDebug() << "File does not exist while trying to read " << path;
        return "";
    }

    QString bookmark = jsonFile.readAll();

    return bookmark;
}

void MainWindow::on_buttonAddBookmark_clicked()
{
    NewBookmark nb(this);
    nb.show();
    int result = nb.exec();
    if(result == QDialog::Accepted)
    {
        qDebug() << "User added a bookmark: name" << nb.getName()
                 << "; browser " << nb.getBrowser()
                 << "; url " << nb.getUrl();

        QJsonObject jsonObject;
        jsonObject.insert("version", "0.1");
        jsonObject.insert("url", nb.getUrl());
        jsonObject.insert("browser", nb.getBrowser());
        QJsonDocument writeDocument(jsonObject);
        QString outputFilename(nb.getName());
        outputFilename += ".json";
        QFileInfo selection = GetSelectedBookmark();
        qDebug() << (selection.isDir() ? "selection is a directory" : "selection is a bookmark");
        QDir directory(selection.isDir() ? selection.filePath() : selection.path());
        qDebug() << "File will be added to " << directory;
        QString outputFilePath = directory.path().isEmpty()? bookmarkDirectory->filePath(outputFilename) : directory.filePath(outputFilename);
        qDebug() << "path to save json to is" <<  outputFilePath;
        QFile outputFile(outputFilePath);
        outputFile.open(QIODevice::WriteOnly);
        outputFile.write(writeDocument.toJson());
        outputFile.close();

        FaviconDownloader *downloader = new FaviconDownloader(outputFilePath, nb.getUrl());
        connect(downloader, SIGNAL(finished(QNetworkReply*)), downloader, SLOT(deleteLater()));
    }
}

void MainWindow::on_pushCreateFolder_clicked()
{
    NewFolder nf(this);
    nf.show();
    int result = nf.exec();
    if(result == QDialog::Accepted)
    {
        qDebug() << "User added a folder:" << nf.getFolderName();
        QFileInfo bookmark = GetSelectedBookmark();
        qDebug() << "Folder will be added to " << bookmark.absoluteDir();
        qDebug() << bookmark.path();
        qDebug() << bookmark.filePath();
        QString directory = bookmark.isDir() ? bookmark.filePath() : bookmark.path();
        QDir bookmarkRoot(directory);
        bookmarkRoot.mkdir(nf.getFolderName());
    }
}

void MainWindow::on_pushDelete_clicked()
{
    QFileInfo bookmarkToDelete = GetSelectedBookmark();
    if(bookmarkToDelete.isDir())
    {
        QDir(bookmarkToDelete.absoluteFilePath()).removeRecursively();
    }
    else
    {
        QFile::remove(bookmarkToDelete.absoluteFilePath());
    }
}

void MainWindow::launchBraveUrl(QString url)
{
    QString program("C:/Program Files/BraveSoftware/Brave-Browser/Application/brave.exe");
    QStringList arguments;
    arguments << url;
    arguments << "-window-size=\"400,300\"";
    arguments << "-window-position=\"0,0\"";
    QProcess::startDetached(program, arguments);
}

void MainWindow::on_pushButton_2_clicked()
{
    launchBraveUrl("");
}

void MainWindow::launchIEUrl(QString url)
{
    QString program("C:/Program Files/Internet Explorer/iexplore.exe");
    QStringList arguments;
    arguments << url;
    QProcess::startDetached(program, arguments);
    QThread::sleep(5);
}

void MainWindow::on_pushIE_clicked()
{
    launchIEUrl("");
}

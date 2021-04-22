#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>


QT_BEGIN_NAMESPACE

class QDir;
class QFileInfo;
class QFile;
class QMutex;

namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initTreeView();
    QFileInfo GetSelectedBookmark();
    QRect GetCurrentScreenGeometry();
    QPair<bool, QJsonDocument> readJson(QString filename);
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void on_pushButton_clicked();
    void onPopupMenuClicked();
    void on_pushStartChrome_clicked();
    void on_startEdge_clicked();
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_buttonAddBookmark_clicked();
    void on_pushCreateFolder_clicked();
    void on_pushDelete_clicked();
    void on_pushButton_2_clicked();
    void on_pushIE_clicked();

private:
    static QFile* logfile;
    static QMutex* mutex;

    void loadSettings();
    void launchChromeUrl(QString url);
    void launchBraveUrl(QString url);
    void launchIEUrl(QString url);
    QString readJsonFile(QString path);
    Ui::MainWindow *ui;
    QMenu *contextMenu;
    QAction *popupAction;
    QDir* bookmarkDirectory;
    QVector<QPair<QString, QString>> browsers;
    void resizeIEWindow();
    void writeBrowsersToJson(QJsonObject& jsonObject);
    void launch(QString program, QString url);
};

#endif // MAINWINDOW_H

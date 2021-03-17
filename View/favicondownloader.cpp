#include "favicondownloader.h"

#include <Qurl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileInfo>
#include <QDir>

FaviconDownloader::FaviconDownloader(QString iconPath, QString urlPath)
{
    this->iconPath = iconPath;
    QUrl url = QUrl(urlPath);
    QString faviconUrl = url.toString(QUrl::RemovePath) + "/favicon.ico";
    qDebug() << faviconUrl;
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_queryFinish(QNetworkReply*)));
    connect(mgr, SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));
    mgr->get(request);

}

void FaviconDownloader::on_queryFinish(QNetworkReply *reply)
{
    QFileInfo fileInfo(iconPath);
    QString iconFile = QDir(fileInfo.absolutePath()).filePath(fileInfo.completeBaseName()) + ".ico";
    QFile file(iconFile);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
}

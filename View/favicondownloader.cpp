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
    const char* mgrSslSignal = SIGNAL(sslErrors(QNetworkReply* reply, const QList<QSslError>& errors));
    const char* sslSlot = SLOT(on_sslErrors(QNetworkReply* reply, const QList<QSslError>& errors));
    connect(mgr, mgrSslSignal, this, sslSlot);
    mgr->get(request);

}

FaviconDownloader::~FaviconDownloader()
{

}

void FaviconDownloader::on_deleteLater()
{

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

void FaviconDownloader::on_SslErrors(QNetworkReply* reply, const QList<QSslError>& errors)
{
    QList<QSslError>::const_iterator i;
    for(i = errors.begin(); i != errors.end(); ++i)
    {
        qDebug() << i->errorString();
    }
    qDebug() << "ssl errors complete";
}

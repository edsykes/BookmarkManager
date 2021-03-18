#ifndef FAVICONDOWNLOADER_H
#define FAVICONDOWNLOADER_H

#include <QNetworkReply>
#include <QObject>

class FaviconDownloader : public QObject
{
    Q_OBJECT
public:


    FaviconDownloader(QString iconPath, QString url);
    ~FaviconDownloader();

private slots:
    void on_deleteLater();
    void on_queryFinish(QNetworkReply* reply);
    void on_SslErrors(QNetworkReply* reply, const QList<QSslError>& errors);

private:
    QString iconPath;

};

#endif // FAVICONDOWNLOADER_H

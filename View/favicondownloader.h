#ifndef FAVICONDOWNLOADER_H
#define FAVICONDOWNLOADER_H

#include <QNetworkReply>
#include <QObject>

class FaviconDownloader : public QObject
{
public:
    FaviconDownloader(QString iconPath, QString url);

private slots:
    void on_deleteLater();
    void on_queryFinish(QNetworkReply* reply);

private:
    QString iconPath;

};

#endif // FAVICONDOWNLOADER_H

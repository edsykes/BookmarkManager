#include "bookmarkiconprovider.h"

#include <QDir>

BookmarkIconProvider::BookmarkIconProvider()
{

}

QIcon BookmarkIconProvider::icon(const QFileInfo &info) const
{
    if(info.suffix() == "bmk"){

        QString iconFile = QDir(info.absolutePath()).filePath(info.completeBaseName()) + ".ico";
        if(QFileInfo::exists(iconFile)){
            return QIcon(iconFile);
        }
        return QIcon("C:/Users/edsyk/OneDrive/Bookmarks/favicon.ico");
    }

    return QFileIconProvider::icon(info);
}

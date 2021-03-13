#ifndef BOOKMARKICONPROVIDER_H
#define BOOKMARKICONPROVIDER_H

#include <QFileIconProvider>

class BookmarkIconProvider : public QFileIconProvider
{
public:
    BookmarkIconProvider();
    QIcon icon(const QFileInfo& info) const;
};

#endif // BOOKMARKICONPROVIDER_H

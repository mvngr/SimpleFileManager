#ifndef FILECLIPBOARD_H
#define FILECLIPBOARD_H

#include <QDir>

class FileClipboard {
public:
    static void paste(const QDir& directory);
};

#endif // FILECLIPBOARD_H

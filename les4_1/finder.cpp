#include "finder.h"

#include <QDir>

Finder::Finder(const QString& dir, const QString& fileName, QObject* parent) :
    QThread {parent},
    dir{dir},
    fileName{fileName},
    stopped{true}
{

}

void Finder::run()
{
    stopped = false;
    QStringList dirs = {dir};
    for (int i = 0; dirs.count() && !stopped; )
    {
        QDir search(dirs.at(i));

        search.setFilter(QDir::Hidden | QDir::Dirs | QDir::NoSymLinks);
        QStringList foundDirs = search.entryList();

        int amount = foundDirs.count();
        for (int j = 0; j < amount && !stopped; j++)
        {
            QString newPath;
            if (dirs.at(i).back() == '/')
            {
                newPath = dirs.at(i) + foundDirs[j];
            }
            else
            {
                newPath = dirs.at(i) + "/" + foundDirs[j];
            }
            if (newPath.indexOf("/.") == -1)
            {
                dirs << newPath;
            }
        }

        search.setFilter(QDir::Hidden | QDir::Files | QDir::NoSymLinks);
        QStringList foundFiles = search.entryList();
        amount = foundFiles.count();
        for (int j = 0; j < amount && !stopped; j++)
        {
            QString file = foundFiles.at(j);
            if (file.indexOf(fileName) != -1)
            {
                int index = file.indexOf(".txt");
                if (index != -1 && file.length() - 4 == index)
                {
                    emit FileFound(dirs.at(i) + "/" + file);
                }
            }
        }
        dirs.removeAt(0);
    }
    emit ThreadStopped();
}

void Finder::Stop(bool stop)
{
    stopped = stop;
}

bool Finder::IsStopped() const
{
    return stopped;
}

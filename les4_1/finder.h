#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QThread>

class Finder : public QThread
{
    Q_OBJECT
public:
    explicit Finder(const QString& dir, const QString& fileName, QObject *parent = nullptr);
    void run() override;
    void Stop(bool stop);
    bool IsStopped() const;

signals:
    void ThreadStopped();
    void FileFound(const QString& path);

private:
    QString dir;
    QString fileName;
    bool stopped;

};

#endif // FINDER_H

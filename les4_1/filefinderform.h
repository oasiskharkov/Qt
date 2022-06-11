#ifndef FILEFINDERFORM_H
#define FILEFINDERFORM_H

#include <QWidget>
#include <QStringListModel>
#include <QItemSelectionModel>
#include <QMutex>
#include "service.h"
#include "finder.h"

namespace Ui {
class FileFinderForm;
}

class FileFinderForm : public QWidget
{
    Q_OBJECT

public:
    explicit FileFinderForm(QWidget *parent = nullptr);
    ~FileFinderForm();
    void RetranslateUi();
    void ResetView();

signals:
    void OpenFoundFile(const QString& path);
private slots:
    void Clear();
    void InputPath();
    void SearchFile();
    void StopSearch();
    void OpenSelectedFile();
    void WriteEntryToList(const QString& path);
    void SearchStopped();


private:
    void Init();
    void ResetFinder();
    void SetupButtons();

private:
    Ui::FileFinderForm *ui;
    QStringListModel model;
    QItemSelectionModel selectionModel;
    QSharedPointer<Finder> finder;
    QMutex mutex;
    bool searchStopped;
};

#endif // FILEFINDERFORM_H

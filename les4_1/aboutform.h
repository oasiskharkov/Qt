#ifndef ABOUTFORM_H
#define ABOUTFORM_H

#include <QWidget>
#include "service.h"


namespace Ui {
class AboutForm;
}

class AboutForm : public QWidget
{
    Q_OBJECT

public:
    explicit AboutForm(QWidget *parent = nullptr);
    ~AboutForm();
    void RetranslateUi(Langs lang);
    void SetTheme(Theme theme);

private:
    void Init();

private:
    Ui::AboutForm *ui;
    QString text_eng;
    QString text_rus;
};

#endif // ABOUTFORM_H

#ifndef HELPFORM_H
#define HELPFORM_H

#include <QWidget>
#include "service.h"

namespace Ui {
class HelpForm;
}

class HelpForm : public QWidget
{
    Q_OBJECT

public:
    explicit HelpForm(QWidget *parent = nullptr);
    ~HelpForm();
    void RetranslateUi(Langs lang);
    void SetTheme(Theme theme);

private:
    void Init();

private:
    Ui::HelpForm *ui;
    QString text_eng;
    QString text_rus;

};

#endif // HELPFORM_H

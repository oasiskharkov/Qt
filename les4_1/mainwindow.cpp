#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QClipboard>
#include <QMimeData>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTime>

MainWindow::MainWindow(QApplication& app, QWidget *parent)
    :
      QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , application(app)
    , model(new QFileSystemModel)
    , filePath("")
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    translator.load(langsPath[Langs::ENG]);
    application.installTranslator(&translator);

    aboutForm = new AboutForm(this);
    helpForm = new HelpForm(this);
    fileFinderForm = new FileFinderForm(this);

    ui->explorer_treeView->setModel(model);

    model->setRootPath(QDir::currentPath());
    model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Drives);
    model->setNameFilters({"*.txt"});
    model->setNameFilterDisables(false);

    for(int i = 1; i < model->columnCount(); ++i)
    {
        ui->explorer_treeView->hideColumn(i);
    }
    ui->explorer_treeView->setHeaderHidden(true);
    ui->explorer_treeView->setColumnWidth(0, 350);
    ui->explorer_treeView->hide();

    connect(ui->explorer_treeView, &QTreeView::clicked, this, &MainWindow::TreeViewItemClicked);
    connect(this, &MainWindow::TreeViewSelectItem, this, &MainWindow::OnItemSelected);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::OnTextChanged);
    connect(fileFinderForm, &FileFinderForm::OpenFoundFile, this, &MainWindow::OpenFoundFile);

    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    settingsMenu = new QMenu(this);
    viewMenu = new QMenu(this);
    refMenu = new QMenu(this);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(settingsMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(refMenu);

    newAction = fileMenu->addAction("", this, SLOT(NewFile()), Qt::CTRL + Qt::Key_N);
    openAction = fileMenu->addAction("", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    readOnlyAction = fileMenu->addAction("", this, SLOT(ReadOnlyFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    saveAction = fileMenu->addAction("", this, SLOT(SaveFile()), Qt::CTRL + Qt::Key_S);
    saveAsAction = fileMenu->addAction("", this, SLOT(SaveFileAs()), Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    closeAction = fileMenu->addAction("", this, SLOT(CloseFile()), Qt::CTRL + Qt::SHIFT + Qt::Key_C);
    findFileAction = fileMenu->addAction("", this, SLOT(FindFile()), Qt::CTRL + Qt::Key_F);
    fileMenu->addSeparator();
    printAction = fileMenu->addAction("", this, SLOT(PrintFile()), Qt::CTRL + Qt::Key_P);
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction("", this, SLOT(Exit()), Qt::ALT + Qt::Key_F4);

    cutAction = editMenu->addAction("", this, SLOT(Cut()), Qt::CTRL + Qt::Key_X);
    copyAction = editMenu->addAction("", this, SLOT(Copy()), Qt::CTRL + Qt::Key_C);
    pasteAction = editMenu->addAction("", this, SLOT(Paste()), Qt::CTRL + Qt::Key_V);
    deleteAction = editMenu->addAction("", this, SLOT(Delete()), Qt::Key_Delete);
    selectAllAction = editMenu->addAction("", this, SLOT(SelectAll()), Qt::CTRL + Qt::Key_A);

    editMenu->addSeparator();
    insertDateAction = editMenu->addAction("", this, SLOT(InsertDate()), Qt::CTRL + Qt::Key_D);
    insertTimeAction = editMenu->addAction("", this, SLOT(InsertTime()), Qt::CTRL + Qt::Key_T);

    editMenu->addSeparator();
    clearAction = editMenu->addAction("", this, SLOT(Clear()), Qt::CTRL + Qt::Key_K);

    editMenu->addSeparator();
    alignSubMenu = new QMenu(editMenu);
    editMenu->addMenu(alignSubMenu);
    alignLeftAction = alignSubMenu->addAction("", this, SLOT(AlignLeft()));
    alignCenterAction = alignSubMenu->addAction("", this, SLOT(AlignCenter()));
    alignRightAction = alignSubMenu->addAction("", this, SLOT(AlignRight()));

    editMenu->addSeparator();
    formatSubMenu = new QMenu(editMenu);
    editMenu->addMenu(formatSubMenu);

    copyFormatAction = formatSubMenu->addAction("", this, SLOT(CopyFormat()));
    applyFormatAction = formatSubMenu->addAction("", this, SLOT(ApplyFormat()));
    resetFormatAction = formatSubMenu->addAction("", this, SLOT(ResetFormat()));

    langSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(langSubMenu);

    engCheckable = langSubMenu->addAction("", this, SLOT(CheckEnglish()));
    engCheckable->setCheckable(true);
    engCheckable->setChecked(true);

    rusCheckable = langSubMenu->addAction("", this, SLOT(CheckRussian()));
    rusCheckable->setCheckable(true);
    rusCheckable->setChecked(false);

    shortcutSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(shortcutSubMenu);

    f2Checkable = shortcutSubMenu->addAction("", this, SLOT(F2()));
    f2Checkable->setCheckable(true);
    f2Checkable->setChecked(false);

    f3Checkable = shortcutSubMenu->addAction("", this, SLOT(F3()));
    f3Checkable->setCheckable(true);
    f3Checkable->setChecked(false);

    f4Checkable = shortcutSubMenu->addAction("", this, SLOT(F4()));
    f4Checkable->setCheckable(true);
    f4Checkable->setChecked(false);

    f5Checkable = shortcutSubMenu->addAction("", this, SLOT(F5()));
    f5Checkable->setCheckable(true);
    f5Checkable->setChecked(false);

    f6Checkable = shortcutSubMenu->addAction("", this, SLOT(F6()));
    f6Checkable->setCheckable(true);
    f6Checkable->setChecked(false);

    f7Checkable = shortcutSubMenu->addAction("", this, SLOT(F7()));
    f7Checkable->setCheckable(true);
    f7Checkable->setChecked(false);

    themeSubMenu = new QMenu(settingsMenu);
    settingsMenu->addMenu(themeSubMenu);

    lightCheckable = themeSubMenu->addAction("", this, SLOT(SetLightTheme()));
    lightCheckable->setCheckable(true);
    lightCheckable->setChecked(true);

    darkCheckable = themeSubMenu->addAction("", this, SLOT(SetDarkTheme()));
    darkCheckable->setCheckable(true);
    darkCheckable->setChecked(false);

    settingsMenu->addSeparator();
    fontAction = settingsMenu->addAction("", this, SLOT(ChangeFont()));

    explorerCheckable = viewMenu->addAction("", this, SLOT(ShowExplorer()), Qt::CTRL + Qt::Key_E);
    explorerCheckable->setCheckable(true);
    explorerCheckable->setChecked(false);

    aboutAction = refMenu->addAction("", this, SLOT(About()), Qt::Key_F12);
    refMenu->addSeparator();
    helpAction = refMenu->addAction("", this, SLOT(Help()), Qt::Key_F1);

    fileInfoLabel = new QLabel(this);
    fileInfoLabel->alignment().setFlag(Qt::AlignmentFlag::AlignLeft);
    statusBar()->addWidget(fileInfoLabel);

    QFile file(":/dark_style");
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        QTextStream stream(&file);
        darkStyle = stream.readAll();
        file.close();
    }

    RetranslateUi(Langs::ENG);
}

void MainWindow::RetranslateUi(Langs lang)
{
    setWindowTitle(tr("Text Editor 2.0"));
    filter = trUtf8("Text File(*.txt);;All Files(*.*)");

    fileMenu->setTitle(tr("&File"));
    editMenu->setTitle(tr("&Edit"));
    settingsMenu->setTitle(tr("&Settings"));
    viewMenu->setTitle(tr("&View"));
    refMenu->setTitle(tr("&Reference"));

    newAction->setText(tr("&New"));
    openAction->setText(tr("&Open"));
    readOnlyAction->setText(tr("&Read Only"));
    saveAction->setText(tr("&Save"));
    saveAsAction->setText(tr("&Save As"));
    closeAction->setText(tr("&Close"));
    findFileAction->setText(tr("&Find File"));
    printAction->setText(tr("&Print"));
    exitAction->setText(tr("&Exit"));

    cutAction->setText(tr("&Cut"));
    copyAction->setText(tr("&Copy"));
    pasteAction->setText(tr("&Paste"));
    deleteAction->setText(tr("&Delete"));
    selectAllAction->setText(tr("&Select All"));
    clearAction->setText(tr("&Clear"));
    insertDateAction->setText(tr("&Insert Date"));
    insertTimeAction->setText(tr("&Insert Time"));

    alignSubMenu->setTitle(tr("&Align"));
    alignLeftAction->setText(tr("&Left"));
    alignCenterAction->setText(tr("&Center"));
    alignRightAction->setText(tr("&Right"));

    formatSubMenu->setTitle(tr("&Format"));
    copyFormatAction->setText(tr("&Copy Format"));
    applyFormatAction->setText(tr("&Apply Format"));
    resetFormatAction->setText(tr("&Reset Format"));

    langSubMenu->setTitle(tr("&Language"));
    engCheckable->setText(tr("&English"));
    rusCheckable->setText(tr("&Russian"));

    shortcutSubMenu->setTitle(tr("&Shortcuts"));
    f2Checkable->setText(tr("&New -> F2"));
    f3Checkable->setText(tr("&Open -> F3"));;
    f4Checkable->setText(tr("&Read Only -> F4"));
    f5Checkable->setText(tr("&Save -> F5"));
    f6Checkable->setText(tr("&Save As -> F6"));
    f7Checkable->setText(tr("&Close -> F7"));

    themeSubMenu->setTitle(tr("&Theme"));
    lightCheckable->setText(tr("&Light"));
    darkCheckable->setText(tr("&Dark"));

    fontAction->setText(tr("&Font"));

    explorerCheckable->setText(tr("&Explorer"));

    aboutAction->setText(tr("&About"));
    helpAction->setText(tr("&Help"));

    aboutForm->RetranslateUi(lang);
    helpForm->RetranslateUi(lang);
    fileFinderForm->RetranslateUi();
}

void MainWindow::NewFile()
{
    ui->textEdit->setReadOnly(false);
    ui->textEdit->clear();
    filePath = "";
    OnTextChanged();
}

void MainWindow::OpenFileFunc()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File", QDir::current().path(), filter);
    if (path.length() > 0)
    {
        int index = path.indexOf(".txt");
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && path.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                filePath = path;
                OnTextChanged();
                file.close();
            }
        }
    }
}

void MainWindow::SetTheme(Theme theme)
{
    switch (theme)
    {
    case Theme::LIGHT:
        application.setStyleSheet("");
        break;
    case Theme::DARK:
        application.setStyleSheet(darkStyle);
        break;
    }
}

void MainWindow::ShowCurrentPath(const QString& path)
{
    QStringList parts = path.split("/");
    if(parts.size())
    {
        for (int i = 0; i < parts.size(); ++i)
        {
            QString currentPath;
            for (int j = 0; j <= i; ++j)
            {
                currentPath.append(parts.at(j)).append("/");
            }
            ui->explorer_treeView->expand(model->index(currentPath));
        }
    }
}

void MainWindow::Align(Qt::Alignment alignment)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(alignment);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::OpenFile()
{
    OpenFileFunc();
    ui->textEdit->setReadOnly(false);
}

void MainWindow::ReadOnlyFile()
{
    OpenFileFunc();
    ui->textEdit->setReadOnly(true);
}

void MainWindow::SaveFile()
{
    if(filePath.isEmpty())
    {
        SaveFileAs();
    }
    else
    {
        QFile file(filePath);
        if (file.open(QFile::WriteOnly))
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();
            OnTextChanged();
        }
    }
}

void MainWindow::SaveFileAs()
{
    QString s = QFileDialog::getSaveFileName(this, "Save File As", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(s);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                filePath = s;
                OnTextChanged();
            }
        }
    }
}

void MainWindow::PrintFile()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    ui->textEdit->print(&printer);
}

void MainWindow::CloseFile()
{
    ui->textEdit->clear();
    ui->textEdit->setReadOnly(false);
    filePath = "";
    OnTextChanged();
}

void MainWindow::FindFile()
{
    if(fileFinderForm)
    {
        fileFinderForm->ResetView();
        fileFinderForm->show();
    }
}

void MainWindow::Exit()
{
    this->close();
}

void MainWindow::Cut()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(QClipboard* c = QApplication::clipboard())
    {
        c->setText(cursor.selectedText());
    }
    cursor.removeSelectedText();
}

void MainWindow::Copy()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(QClipboard* c = QApplication::clipboard())
    {
        c->setText(cursor.selectedText());
    }
}

void MainWindow::Paste()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(QClipboard* c = QApplication::clipboard())
    {
        if(const QMimeData* m = c->mimeData())
        {
            if(m->hasText())
            {
                cursor.insertText(m->text());
            }
        }
    }
}

void MainWindow::Delete()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.removeSelectedText();
}

void MainWindow::SelectAll()
{
    ui->textEdit->selectAll();
}

void MainWindow::Clear()
{
    ui->textEdit->clear();
}

void MainWindow::InsertDate()
{
    InsertDateTime("dd-MM-yyyy");
}

void MainWindow::InsertTime()
{
    InsertDateTime("HH:mm:ss");
}

void MainWindow::InsertDateTime(const QString& format)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.toString(format);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertText(date);
}

void MainWindow::AlignLeft()
{
    Align(Qt::AlignLeft);
}

void MainWindow::AlignCenter()
{
    Align(Qt::AlignCenter);
}

void MainWindow::AlignRight()
{
    Align(Qt::AlignRight);
}

void MainWindow::CopyFormat()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    Qt::Alignment alignment = cursor.blockFormat().alignment();
    QFont font = cursor.charFormat().font();
    format.first = font;
    format.second = alignment;
    formatCopied = true;
}

void MainWindow::ApplyFormat()
{
   if(formatCopied)
   {
       QTextCursor cursor = ui->textEdit->textCursor();
       QTextBlockFormat textBlockFormat = cursor.blockFormat();
       textBlockFormat.setAlignment(format.second);
       cursor.mergeBlockFormat(textBlockFormat);
       ui->textEdit->setTextCursor(cursor);

       QTextCharFormat tcf;
       tcf.setFont(format.first);
       cursor.setCharFormat(tcf);
   }
}

void MainWindow::ResetFormat()
{
    formatCopied = false;
}

void MainWindow::CheckEnglish()
{
    if(engCheckable->isChecked())
    {
        rusCheckable->setChecked(false);
        translator.load(langsPath[Langs::ENG]);
        RetranslateUi(Langs::ENG);
    }
    else
    {
        rusCheckable->setChecked(true);
    }
}

void MainWindow::CheckRussian()
{
    if(rusCheckable->isChecked())
    {
        engCheckable->setChecked(false);
        translator.load(langsPath[Langs::RUS]);
        RetranslateUi(Langs::RUS);
    }
    else
    {
        engCheckable->setChecked(true);
    }
}

void MainWindow::About()
{
    if(aboutForm)
    {
        aboutForm->show();
    }
}

void MainWindow::Help()
{
    if(helpForm)
    {
        helpForm->show();
    }
}

void MainWindow::F2()
{
    if(f2Checkable->isChecked())
    {
        newAction->setShortcut(Qt::Key_F2);
    }
    else
    {
        newAction->setShortcut(Qt::CTRL + Qt::Key_N);
    }
}

void MainWindow::F3()
{
    if(f3Checkable->isChecked())
    {
        openAction->setShortcut(Qt::Key_F3);
    }
    else
    {
        openAction->setShortcut(Qt::CTRL + Qt::Key_O);
    }
}

void MainWindow::F4()
{
    if(f4Checkable->isChecked())
    {
        readOnlyAction->setShortcut(Qt::Key_F4);
    }
    else
    {
        readOnlyAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    }
}

void MainWindow::F5()
{
    if(f5Checkable->isChecked())
    {
        saveAction->setShortcut(Qt::Key_F5);
    }
    else
    {
        saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    }
}

void MainWindow::F6()
{
    if(f6Checkable->isChecked())
    {
        saveAsAction->setShortcut(Qt::Key_F6);
    }
    else
    {
        saveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    }
}

void MainWindow::F7()
{
    if(f7Checkable->isChecked())
    {
        closeAction->setShortcut(Qt::Key_F7);
    }
    else
    {
        closeAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_C);
    }
}

void MainWindow::SetLightTheme()
{
    if(lightCheckable->isChecked())
    {
        darkCheckable->setChecked(false);
        SetTheme(Theme::LIGHT);
    }
    else
    {
        darkCheckable->setChecked(true);
    }
}

void MainWindow::SetDarkTheme()
{
    if(darkCheckable->isChecked())
    {
        lightCheckable->setChecked(false);
        SetTheme(Theme::DARK);
    }
    else
    {
        lightCheckable->setChecked(true);
    }
}

void MainWindow::ChangeFont()
{
    QFont font = ui->textEdit->textCursor().charFormat().font();
    QFontDialog fntDlg(font, this);
    bool answer;
    font = fntDlg.getFont(&answer);

    if (answer)
    {
        QTextCharFormat tcf;
        tcf.setFont(font);
        ui->textEdit->textCursor().setCharFormat(tcf);
    }
}

void MainWindow::ShowExplorer()
{
    if(explorerCheckable->isChecked())
    {
        ui->explorer_treeView->show();
    }
    else
    {
        ui->explorer_treeView->hide();
    }
}

void MainWindow::TreeViewItemClicked(const QModelIndex &index)
{
    QString filePath = model->filePath(index);
    emit TreeViewSelectItem(filePath);
}

void MainWindow::OnItemSelected(const QString& path)
{
    if (path.length() > 0)
    {
        int index = path.indexOf(".txt");
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && path.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                filePath = path;
                OnTextChanged();
                file.close();
            }
        }
    }
}

void MainWindow::OnTextChanged()
{
    if(!filePath.isEmpty())
    {
        fileInfoLabel->setText(filePath + "    " + QString::number(ui->textEdit->toPlainText().length()) + " bytes");
    }
    else
    {
        fileInfoLabel->clear();
    }
}

void MainWindow::OpenFoundFile(const QString& path)
{
    if(explorerCheckable->isChecked())
    {
        ShowCurrentPath(path);
    }
    OnItemSelected(path);
}


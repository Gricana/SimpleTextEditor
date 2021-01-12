#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QTextCodec>
#include <QTranslator>
#include <QProcess>
#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#endif

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow), settings(QSettings::NativeFormat, QSettings::UserScope, "IT", qApp->applicationName())
{
    ui->setupUi(this);
    settingsDialog = new SettingsDialog(this);
    replaceDialog = new ReplaceDialog(this);
    searchDialog = new SearchDialog(this);

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    setWindowIcon(QIcon(":/actions/resources/images/text_editor_icon.ico"));
    searchDialog->setWindowIcon(QIcon(":/actions/resources/images/text_editor_icon.ico"));
    replaceDialog->setWindowIcon(QIcon(":/actions/resources/images/text_editor_icon.ico"));
    settingsDialog->setWindowIcon(QIcon(":/actions/resources/images/text_editor_icon.ico"));
    ui->action_Undo->setShortcut(QKeySequence::Undo);
    ui->action_Redo->setShortcut(QKeySequence::Redo);
    ui->action_Cut->setShortcut(QKeySequence::Cut);
    ui->action_Copy->setShortcut(QKeySequence::Copy);
    ui->action_Paste->setShortcut(QKeySequence::Paste);
    ui->action_Select_all->setShortcut(QKeySequence::SelectAll);
    ui->action_New->setShortcut(QKeySequence::New);
    ui->action_Open->setShortcut(QKeySequence::Open);
    ui->action_Save->setShortcut(QKeySequence::Save);
    ui->action_Exit->setShortcut(QKeySequence::Quit);

    ui->action_New->setIcon(QIcon(":/actions/resources/images/new.ico"));
    ui->action_Open->setIcon(QIcon(":/actions/resources/images/open.ico"));
    ui->action_Save->setIcon(QIcon(":/actions/resources/images/save.ico"));
    ui->action_Exit->setIcon(QIcon(":/actions/resources/images/exit.ico"));
    ui->action_Undo->setIcon(QIcon(":/actions/resources/images/undo.ico"));
    ui->action_Redo->setIcon(QIcon(":/actions/resources/images/redo.ico"));
    ui->action_Select_all->setIcon(QIcon(":/actions/resources/images/select_all.ico"));
    ui->action_Copy->setIcon(QIcon(":/actions/resources/images/copy.ico"));
    ui->action_Paste->setIcon(QIcon(":/actions/resources/images/paste.ico"));
    ui->action_Cut->setIcon(QIcon(":/actions/resources/images/cut.ico"));
    ui->action_About_Qt->setIcon(QIcon(":/actions/resources/images/about_qt.ico"));
    ui->action_About_program->setIcon(QIcon(":/actions/resources/images/about_program.ico"));
    ui->action_Settings->setIcon(QIcon(":/actions/resources/images/settings.ico"));
    ui->action_Date_and_time->setIcon(QIcon(":/actions/resources/images/date_time.ico"));
     ui->action_Go_to_the->setIcon(QIcon(":/actions/resources/images/go_to.ico"));
     ui->action_Font->setIcon(QIcon(":/actions/resources/images/font.ico"));
     ui->menu_Color->setIcon(QIcon(":/actions/resources/images/color.ico"));
     ui->action_Zoom_in->setIcon(QIcon(":/actions/resources/images/zoom_in.ico"));
     ui->action_Zoom_out->setIcon(QIcon(":/actions/resources/images/zoom_out.ico"));
     ui->action_Default_zoom->setIcon(QIcon(":/actions/resources/images/default_zoom.ico"));
     ui->action_Preview->setIcon(QIcon(":/actions/resources/images/preview.ico"));
     ui->action_Print->setIcon(QIcon(":/actions/resources/images/print.ico"));
      ui->action_Find->setIcon(QIcon(":/actions/resources/images/find.ico"));
      ui->action_Replace->setIcon(QIcon(":/actions/resources/images/replace.ico"));
      ui->menu_Language->setIcon(QIcon(":/actions/resources/images/language.ico"));
      ui->action_Russian->setIcon(QIcon(":/actions/resources/images/russian.ico"));
      ui->action_English->setIcon(QIcon(":/actions/resources/images/english.ico"));

    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(slotNew()), Qt::UniqueConnection);
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(slotOpen()), Qt::UniqueConnection);
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(ui->action_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()), Qt::UniqueConnection);
    connect(ui->action_About_program, SIGNAL(triggered()), this, SLOT(slotAboutProgram()), Qt::UniqueConnection);
    connect(ui->action_Settings, SIGNAL(triggered()), this, SLOT(showPreferencesDialog()));
    connect(ui->action_Find, SIGNAL(triggered()), this, SLOT(showSearchDialog()), Qt::UniqueConnection);
    connect(ui->action_Replace, SIGNAL(triggered()), this, SLOT(showReplaceDialog()), Qt::UniqueConnection);
    connect(settingsDialog, SIGNAL(accepted()), this, SLOT(slotPreferencesAccepted()), Qt::UniqueConnection);
    connect(searchDialog, SIGNAL(accepted()), this, SLOT(slotFindText()), Qt::UniqueConnection);
    connect(replaceDialog, SIGNAL(accepted()), this, SLOT(slotReplaceText()), Qt::UniqueConnection);
    connect(ui->plainTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(slotOutNumberStringAndColumn()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(closeEvent()), Qt::UniqueConnection);
    connect(ui->action_Date_and_time, SIGNAL(triggered()), this, SLOT(slotShowDateAndTime()), Qt::UniqueConnection);
    connect(ui->action_Go_to_the, SIGNAL(triggered()), this, SLOT(slotGoToTheLine()), Qt::UniqueConnection);
    connect(ui->action_Font, SIGNAL(triggered()), this, SLOT(slotSetFont()), Qt::UniqueConnection);
    connect(ui->action_Text, SIGNAL(triggered()), this, SLOT(slotSetColorText()), Qt::UniqueConnection);
    connect(ui->action_Background, SIGNAL(triggered()), this, SLOT(slotSetColorBackground()), Qt::UniqueConnection);
    connect(ui->action_Zoom_in, SIGNAL(triggered()), this, SLOT(slotZoomIn()));
    connect(ui->action_Zoom_out, SIGNAL(triggered()), this, SLOT(slotZoomOut()));
    connect(ui->action_Default_zoom, SIGNAL(triggered()), this, SLOT(slotDefaultZoom()));
    connect(ui->action_Preview, SIGNAL(triggered()), this, SLOT(slotPreview()), Qt::UniqueConnection);
    connect(ui->action_Print, SIGNAL(triggered()), this, SLOT(slotPrint()), Qt::UniqueConnection);
    connect(ui->action_English, SIGNAL(triggered()), this, SLOT(slotEnglishLanguage()), Qt::UniqueConnection);
    connect(ui->action_Russian, SIGNAL(triggered()), this, SLOT(slotRussianLanguage()), Qt::UniqueConnection);
    applyLanguageSetting();
    applyInputSettings();
    readSettings();
    setWindowModified(false);
    slotNew();
}

void MainWindow::applyLanguageSetting()
{
    if (settings.value("/SETTING_LANGUAGE_RUSSIAN", ui->action_Russian->isEnabled()).toBool())
    {
        translatorRussian = new QTranslator(this);
        slotRussianLanguage();
    } else slotEnglishLanguage();
}

void MainWindow::setLanguageSetting()
{
    settings.beginGroup("/SETTINGS_GROUP_VIEW");
    settings.setValue("/SETTING_LANGUAGE_ENGLISH", !ui->action_English->isEnabled());
    settings.setValue("/SETTING_LANGUAGE_RUSSIAN", !ui->action_Russian->isEnabled());
    settings.endGroup();
}

void MainWindow::slotRussianLanguage()
{
    ui->action_Russian->setDisabled(true);
    ui->action_English->setDisabled(false);
    setLanguageSetting();
    askForFileSaveAndClose();
    translatorRussian->load(QString("%1/languages/QReader_ru").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(translatorRussian);
    ui->retranslateUi(this);
    settingsDialog->setRussianLanguage();
    searchDialog->setRussianLanguage();
    replaceDialog->setRussianLanguage();
    setWindowModified(false);
    slotNew();
}

void MainWindow::slotEnglishLanguage()
{
    ui->action_English->setDisabled(true);
    ui->action_Russian->setDisabled(false);
    setLanguageSetting();
    askForFileSaveAndClose();
    QTranslator translatorEnglish(this);
    translatorEnglish.load(QString("%1/languages/QReader_en").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translatorEnglish);
    ui->retranslateUi(this);
    settingsDialog->setEnglishLanguage();
    replaceDialog->setEnglishLanguage();
    searchDialog->setEnglishLanguage();
    setWindowModified(false);
    slotNew();
}

void MainWindow::applyInputSettings()
{
    settings.beginGroup("/SETTINGS_GROUP_VIEW");
    if (settings.value("/SETTING_LIGHT_THEME", settingsDialog->isThemeLight()).toBool()) { isLight = true, isDark = false; }
    if (settings.value("/SETTING_DARK_THEME", settingsDialog->isThemeDark()).toBool()) { isLight = false, isDark = true; }
    app_counter = settings.value("/COUNTER_APP", 1).toInt();
    QString str = tr("This program has been started ") + QString().setNum(app_counter++) + tr(" times");
    ui->statusbar->showMessage(str, 3000);
    int app_width = settings.value("/WIDTH", width()).toInt();
    int app_height = settings.value("/HEIGHT", height()).toInt();
    this->resize(app_width, app_height);
    settings.endGroup();
    ui->plainTextEdit->setFont(font);
    ui->plainTextEdit->setFrameShape(QFrame::NoFrame);
}

void MainWindow::lightTheme()
{
    color = QColor(Qt::white);
    checkingReplace();
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::white);
    p.setColor(QPalette::WindowText, Qt::black);
    p.setColor(QPalette::ButtonText, Qt::black);
    this->setPalette(p);
    ui->menubar->setStyleSheet(QString("background-color: white; color: black;"));
    QPalette pal = ui->plainTextEdit->palette();
    pal.setColor(QPalette::Active, QPalette::Text, Qt::black);
    pal.setColor(QPalette::Inactive, QPalette::Text, Qt::black);
    pal.setColor(QPalette::Active, QPalette::Base, Qt::white);
    pal.setColor(QPalette::Inactive, QPalette::Base, Qt::white);
    ui->plainTextEdit->setPalette(pal);
    ui->menu_File->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_Edit->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_Format->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_About->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_Color->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_Language->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->menu_View->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
    ui->Settings->setStyleSheet("QMenu::item::selected { background-color: #90c8f6; }");
}

void MainWindow::darkTheme()
{
    color = QColor("#2e2f30");
    checkingReplace();
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor("#2e2f30"));
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::ButtonText, Qt::white);
    this->setPalette(p);
    ui->menubar->setStyleSheet(QString("background-color: #2e2f30; color: white;"));
    QPalette pal = ui->plainTextEdit->palette();
    pal.setColor(QPalette::Active, QPalette::Text, Qt::white);
    pal.setColor(QPalette::Inactive, QPalette::Text, Qt::white);
    pal.setColor(QPalette::Active, QPalette::Base, QColor(QString("#2e2f30")));
    pal.setColor(QPalette::Inactive, QPalette::Base, QColor(QString("#2e2f30")));
    ui->plainTextEdit->setPalette(pal);
    ui->menu_File->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_Edit->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_Format->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_About->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_Color->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_Language->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->menu_View->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
    ui->Settings->setStyleSheet("QMenu::item::selected { background-color: #3c5670; }");
}

void MainWindow::updateTitle()
{
    QString title = QString(tr("TextEditor - %1[*]")).arg(fileName);
    setWindowTitle(title);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (askForFileSaveAndClose())
    {
        event->accept();
        return;
    } else {
    event->ignore();
    }
}

void MainWindow::slotNew()
{
    if (askForFileSaveAndClose())
    {
        fileName = "Untitled.txt";
        ui->plainTextEdit->clear();
        setWindowModified(false);
        updateTitle();
    }
}

void MainWindow::slotOpen()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open file . . . "), QDir::homePath(), tr("Text files (*.txt);; Header files (*.h);; Source files (*.cpp);; Data files (*.dat);; CSV-files (*.csv);; All files (*.*)"));
    if (fileName.isEmpty()) { return; }
    if (!askForFileSaveAndClose()){ return; }
    QFile file(FileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileName = FileName;
        ui->plainTextEdit->setPlainText(file.readAll());
        file.close();
        setWindowModified(false);
        updateTitle();
    }
    else {
        QMessageBox::warning(this, tr("Error"), QString(tr("Could not open file %1 for reading")).arg(file.fileName()), QMessageBox::Ok);
    }
}

void MainWindow::slotSave()
{
    if (!isWindowModified()) { return; }
    QString Filename = QFileDialog::getSaveFileName(this, tr("Save file . . . "), QDir::homePath(), tr("Text files (*.txt);;All files (*.*)"));
    if (Filename.isEmpty()) { return; }
    QFile file(Filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fileName = Filename;
        QTextStream writeStream(&file);
        QString document = ui->plainTextEdit->toPlainText();
        writeStream << document;
        file.close();
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(document);
        setWindowModified(false);
        updateTitle();
    }
    else {
        QMessageBox::warning(this, tr("Error"), QString(tr("Could not open file %1 for writing")).arg(file.fileName()), QMessageBox::Ok);
    }
}

bool MainWindow::askForFileSaveAndClose()
{
    if (isWindowModified())
    {
        int result = QMessageBox::question(this, tr("Save changes"), QString(tr("File %1 is modified. Do you want to save your changes?")).arg(fileName), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (QMessageBox::Yes == result) { slotSave(); }
        else {
            if (QMessageBox::Cancel == result) { return false; }
        }
    }
    return true;
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, tr("About app"), QString("%1 v. %2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
}

void MainWindow::readSettings()
{
    settings.beginGroup("/SETTINGS_GROUP_VIEW");

    bool showToolBar = settings.value("/SETTING_SHOW_TOOLBAR", settingsDialog->isShowToolBar()).toBool();
    settingsDialog->setShowToolBar(showToolBar);
    bool showStatusBar = settings.value("/SETTING_SHOW_STATUS_BAR", settingsDialog->isShowStatusBar()).toBool();
    settingsDialog->setShowStatusBar(showStatusBar);
    ui->toolBar->setVisible(showToolBar);
    ui->statusbar->setVisible(showStatusBar);

    bool isLightTheme = settings.value("/SETTING_LIGHT_THEME", settingsDialog->isThemeLight()).toBool();
    settingsDialog->setLightTheme(isLightTheme);
    bool isDarkTheme = settings.value("/SETTING_DARK_THEME", settingsDialog->isThemeDark()).toBool();
    settingsDialog->setDarkTheme(isDarkTheme);
    if (isDarkTheme and isDark == true)
    {
        darkTheme();
        isDark = false; isLight = true;
    }
    if (isLightTheme and isLight == true)
    {
        lightTheme();
        isLight = false; isDark = true;
    }

    bool isWordWrap = settings.value("/SETTING_WORD_WRAP", settingsDialog->isWordWrap()).toBool();
    settingsDialog->setWordWrap(isWordWrap);
    if (isWordWrap) {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->action_Go_to_the->setDisabled(true);
    }
    else {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->action_Go_to_the->setDisabled(false);
    }
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    settings.beginGroup("/SETTINGS_GROUP_VIEW");
    settings.setValue("/WIDTH", width());
    settings.setValue("/HEIGHT", height());
    settings.setValue("/COUNTER_APP", app_counter);
    settings.setValue("/SETTING_SHOW_TOOLBAR", settingsDialog->isShowToolBar());
    settings.setValue("/SETTING_SHOW_STATUS_BAR", settingsDialog->isShowStatusBar());
    settings.setValue("/SETTING_LIGHT_THEME", settingsDialog->isThemeLight());
    settings.setValue("/SETTING_DARK_THEME", settingsDialog->isThemeDark());
    settings.setValue("/SETTING_WORD_WRAP", settingsDialog->isWordWrap());
    settings.endGroup();
}

void MainWindow::showPreferencesDialog()
{
    settingsDialog->show();
}

void MainWindow::slotPreferencesAccepted()
{
    writeSettings();
    readSettings();
}

void MainWindow::slotOutNumberStringAndColumn()
{
    int line = ui->plainTextEdit->textCursor() .blockNumber() + 1;
    int column = ui->plainTextEdit->textCursor().positionInBlock() + 1;
    ui->statusbar->showMessage(QString(tr("Line: %1  Column: %2")).arg(line).arg(column));
}

void MainWindow::slotShowDateAndTime()
{
    QString dateAndTime = QDateTime::currentDateTime().toString(Qt::LocalDate);
    QTextCursor textCursor = QTextCursor(ui->plainTextEdit->document());
    textCursor.movePosition(QTextCursor::End);
    textCursor.insertText(dateAndTime);
}

void MainWindow::slotGoToTheLine()
{
    bool ok;
    int NumberStr = QInputDialog::getInt(this, QString(tr("Go to the line")), QString(tr("Line number")), 0, 0, 2147483647, 1, &ok);
    if (ok)
    {
        if (NumberStr > ui->plainTextEdit-> document()->lineCount()) QMessageBox::information(this, tr("Go to the line"), tr("The line number exceeds the total number of lines"));
        else {
            QTextCursor textCursor = QTextCursor(ui->plainTextEdit->document());
            textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, NumberStr - 1);
            textCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 0);
            ui->plainTextEdit->setTextCursor(textCursor);
        }
    }
}

void MainWindow::slotSetFont()
{
    bool ok;
    font = QFontDialog::getFont(&ok, QFont() , this, QString(tr("Select font")));
    if (ok) ui->plainTextEdit->setFont(font);
    zoomValue = 100;
}

void MainWindow::slotSetColorText()
{
    QColor color = QColorDialog::getColor(QColor(), this, QString(tr("Select color of text")));
    if (color.isValid())
    {
        QPalette p = ui->plainTextEdit->palette();
        p.setColor(QPalette::Active, QPalette::Text, color);
        p.setColor(QPalette::Inactive, QPalette::Text, color);
        ui->plainTextEdit->setPalette(p);
        ui->plainTextEdit->setBackgroundVisible(false);
    }
}

void MainWindow::slotSetColorBackground()
{
    color = QColorDialog::getColor(QColor(), this, QString(tr("Select color of background")));
    if (color.isValid()) {
        checkingReplace();
        QPalette p = ui->plainTextEdit->palette();
        p.setColor(QPalette::Inactive, QPalette::Base, color);
        p.setColor(QPalette::Active, QPalette::Base, color);
        ui->plainTextEdit->setPalette(p);
    }
}

void MainWindow::slotZoomIn()
{
    if (zoomValue * 2 < 1677721600) {
    zoomValue *= 2;
    ui->plainTextEdit->zoomIn(2);
    ui->statusbar->showMessage(QString(tr("Zoom: %1%")).arg(zoomValue));
    } else
        ui->statusbar->showMessage(QString(tr("Zoom: %1%")).arg(zoomValue));
}

void MainWindow::slotZoomOut()
{
    if (zoomValue / 2 > 0) {
    zoomValue /= 2;
    ui->plainTextEdit->zoomOut(2);
    ui->statusbar->showMessage(QString(tr("Zoom: %1%")).arg(zoomValue));
    } else
        ui->statusbar->showMessage(QString(tr("Zoom: %1%")).arg(zoomValue));
}

void MainWindow::slotDefaultZoom()
{
    zoomValue = 100;
    ui->plainTextEdit->setFont(font);
    ui->statusbar->showMessage(QString(tr("Zoom: %1%")).arg(zoomValue));
}

void MainWindow::slotPreview()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif
}

void MainWindow::printPreview(QPrinter *printer)
{
    ui->plainTextEdit->print(printer);
}

void MainWindow::slotPrint()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    if (ui->plainTextEdit->textCursor().hasSelection())
        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dialog->setWindowTitle(tr("Print document"));
    if (dialog->exec() == QDialog::Accepted) ui->plainTextEdit->print(&printer);
    delete dialog;
#endif
}

void MainWindow::showSearchDialog()
{
    searchDialog->show();
}

void MainWindow::showReplaceDialog()
{
    replaceDialog->show();
    checkingReplace();
}

void MainWindow::slotFindText()
{
    if (searchDialog->getText().isEmpty())
    {
        QMessageBox::information(this, tr("Search"), tr("The search bar is empty. <p>We have nothing to look for."), QMessageBox::Ok);
    }
    else {
        QTextCursor cursor(ui->plainTextEdit->textCursor());
        const int cursorPosition = cursor.position();
        ui->plainTextEdit->textCursor().beginEditBlock();
        QTextCharFormat format; format.setBackground(Qt::yellow);
        QString findString = searchDialog->getText();
        if (searchDialog->isFirstOccurrence() and searchDialog->isCaseSensitive())
        {
            if (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(findString, format);
            }
        } else if (searchDialog->isFirstOccurrence() and !searchDialog->isCaseSensitive()) {
                if (ui->plainTextEdit->find(findString)) {
                    ui->plainTextEdit->textCursor().select(QTextCursor::BlockUnderCursor);
                    ui->plainTextEdit->textCursor().insertText(ui->plainTextEdit->textCursor().selectedText(), format);
                }
        } else if (searchDialog->isAllFollowingOccurrences() and searchDialog->isCaseSensitive()) {
            while (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(findString, format);
            }
        } else if (searchDialog->isAllFollowingOccurrences() and !searchDialog->isCaseSensitive()){
            while (ui->plainTextEdit->find(findString)) {
                ui->plainTextEdit->textCursor().select(QTextCursor::BlockUnderCursor);
                ui->plainTextEdit->textCursor().insertText(ui->plainTextEdit->textCursor().selectedText(), format);
            }
        } else if (searchDialog->isAllDocument() and searchDialog->isCaseSensitive()) {
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            while (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(findString, format);
            }
        } else if (searchDialog->isAllDocument() and !searchDialog->isCaseSensitive()){
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            while (ui->plainTextEdit->find(findString)) {
                ui->plainTextEdit->textCursor().select(QTextCursor::BlockUnderCursor);
                ui->plainTextEdit->textCursor().insertText(ui->plainTextEdit->textCursor().selectedText(), format);
            }
        }
        ui->plainTextEdit->textCursor().endEditBlock();
        cursor.setPosition(cursorPosition);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::slotReplaceText()
{
    if (replaceDialog->getTextReplaced().isEmpty() or replaceDialog->getTextReplacing().isEmpty())
    {
        isReplace = false;
        QMessageBox::information(this, tr("Replace"), tr("You didn't enter one of the words. <p>The operation cannot be performed"), QMessageBox::Ok);
    }
    else {
        QTextCursor cursor(ui->plainTextEdit->textCursor());
        const int cursorPosition = cursor.position();
        isReplace = true;
        ui->plainTextEdit->textCursor().beginEditBlock();
        QTextCharFormat format; format.setBackground(Qt::green);
        QString findString = replaceDialog->getTextReplaced();
        QString replaceString = replaceDialog->getTextReplacing();
        if (replaceDialog->isFirstOccurrenceReplace() and replaceDialog->isCaseSensitiveReplace())
        {
            if (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(replaceString, format);
            }
        } else if (replaceDialog->isFirstOccurrenceReplace() and !replaceDialog->isCaseSensitiveReplace()) {
                if (ui->plainTextEdit->find(findString)) {
                    ui->plainTextEdit->textCursor().insertText(replaceString, format);
                }
        } else if (replaceDialog->isAllFollowingReplace() and replaceDialog->isCaseSensitiveReplace()) {
            while (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(replaceString, format);
            }
        } else if (replaceDialog->isAllFollowingReplace() and !replaceDialog->isCaseSensitiveReplace()){
            while (ui->plainTextEdit->find(findString)) {
                ui->plainTextEdit->textCursor().insertText(replaceString, format);
            }
        } else if (replaceDialog->isAllDocumentReplace() and replaceDialog->isCaseSensitiveReplace()) {
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            while (ui->plainTextEdit->find(findString, QTextDocument::FindCaseSensitively)) {
                ui->plainTextEdit->textCursor().insertText(replaceString, format);
            }
        } else if (replaceDialog->isAllDocumentReplace() and !replaceDialog->isCaseSensitiveReplace()){
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            while (ui->plainTextEdit->find(findString)) {
                ui->plainTextEdit->textCursor().insertText(replaceString, format);
            }
        }
        ui->plainTextEdit->textCursor().endEditBlock();
        cursor.setPosition(cursorPosition);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::checkingReplace()
{
    if (isReplace) {
    QTextCursor cursor(ui->plainTextEdit->textCursor());
    const int cursorPosition = cursor.position();
    QString document = ui->plainTextEdit->document()->toPlainText();
    ui->plainTextEdit->clear();
    QTextCharFormat highlight; highlight.setBackground(QColor(color));
    ui->plainTextEdit->textCursor().insertText(document, highlight);
    cursor.setPosition(cursorPosition);
    ui->plainTextEdit->setTextCursor(cursor);
    }
}

MainWindow::~MainWindow()
{
    writeSettings();
    setLanguageSetting();
    delete ui;
    delete settingsDialog;
    delete searchDialog;
    delete replaceDialog;
    delete translatorRussian;
}


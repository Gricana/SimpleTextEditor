#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QSettings>
#include <QDateTime>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow), settingsDialog(new SettingsDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/actions/resources/images/text_editor_icon.ico"));
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

    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(slotNew()), Qt::UniqueConnection);
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(slotNew()), Qt::UniqueConnection);
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(slotOpen()), Qt::UniqueConnection);
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(ui->action_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()), Qt::UniqueConnection);
    connect(ui->action_About_program, SIGNAL(triggered()), this, SLOT(slotAboutProgram()), Qt::UniqueConnection);
    connect(ui->action_Settings, SIGNAL(triggered()), this, SLOT(showPreferencesDialog()));
    connect(settingsDialog, SIGNAL(accepted()), this, SLOT(slotPreferencesAccepted()), Qt::UniqueConnection);
    connect(ui->plainTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(slotOutNumberStringAndColumn()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(closeEvent()), Qt::UniqueConnection);
    connect(ui->action_Date_and_time, SIGNAL(triggered()), this, SLOT(slotShowDateAndTime()), Qt::UniqueConnection);
    connect(ui->action_Go_to_the, SIGNAL(triggered()), this, SLOT(slotGoToTheLine()), Qt::UniqueConnection);
    slotNew();

//    QColor color = QColorDialog::getColor();
//    bool ok;
//    QFont fontDialog = QFontDialog::getFont(&ok, QFont("Times, 12") , this, QString::fromUtf8("Select font"));
}

void MainWindow::updateTitle()
{
    QString title = QString("TextEditor - %1[*]").arg(fileName);
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
        fileName = "UntitledFile";
        ui->plainTextEdit->clear();
        setWindowModified(false);
        updateTitle();
    }
}

void MainWindow::slotOpen()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Open file . . . ", QDir::homePath(), "Text files (*.txt)::All files (*.*)");
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
        QMessageBox::warning(this, "Error", QString("Could not open file %1 for reading").arg(file.fileName()), QMessageBox::Ok);
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
        writeStream << ui->plainTextEdit->toPlainText();
        file.close();
        setWindowModified(false);
    }
    else {
        QMessageBox::warning(this, "Error", QString("Could not open file %1 for writing").arg(file.fileName()), QMessageBox::Ok);
    }
}

bool MainWindow::askForFileSaveAndClose()
{
    if (isWindowModified())
    {
        int result = QMessageBox::question(this, tr("Save changes"), QString(tr("File %1 is modified. Do you want to save your changes?")).arg(fileName), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
        if (QMessageBox::Yes == result) { slotSave(); }
        else {
            if (QMessageBox::Cancel == result) { return false; }
        }
    }
    return true;
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, tr("About"), QString("%1 v. %2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
}

void MainWindow::readSettings()
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "", qApp->applicationName());
    settings.beginGroup("SETTINGS_GROUP_VIEW");
    bool showToolBar = settings.value("SETTING_SHOW_TOOLBAR", settingsDialog->isShowToolBar()).toBool();
    settingsDialog->setShowToolBar(showToolBar);
    bool showStatusBar = settings.value("SETTING_SHOW_STATUS_BAR", settingsDialog->isShowStatusBar()).toBool();
    settingsDialog->setShowStatusBar(showStatusBar);
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "", qApp->applicationName());
    settings.beginGroup("SETTINGS_GROUP_VIEW");
    settings.setValue("SETTING_SHOW_TOOLBAR", settingsDialog->isShowToolBar());
    settings.setValue("SETTING_SHOW_STATUS_BAR", settingsDialog->isShowStatusBar());
    settings.endGroup();
}

void MainWindow::applySettings()
{
    ui->toolBar->setVisible(settingsDialog->isShowToolBar());
    ui->statusbar->setVisible(settingsDialog->isShowStatusBar());
}

void MainWindow::showPreferencesDialog()
{
    settingsDialog->show();
}

void MainWindow::slotPreferencesAccepted()
{
    readSettings();
    writeSettings();
    applySettings();
}

void MainWindow::slotOutNumberStringAndColumn()
{
    int line = ui->plainTextEdit->textCursor() .blockNumber() + 1;
    int column = ui->plainTextEdit->textCursor().positionInBlock() + 1;
    ui->statusbar->showMessage(QString("Line: %1  Column: %2").arg(line).arg(column));
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
    int NumberStr = QInputDialog::getInt(this, QString::fromUtf8("Go to the line"), QString::fromUtf8("Line number"), 0, 0, 2147483647, 1, &ok);
    if (ok)
    {
        if (NumberStr > ui->plainTextEdit-> document()->lineCount()) QMessageBox::information(this, "Go to the line", "The line number exceeds the total number of lines");
        else {
            QTextCursor textCursor = QTextCursor(ui->plainTextEdit->document());
            textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, NumberStr - 1);
            textCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 0);
            ui->plainTextEdit->setTextCursor(textCursor);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settingsDialog;
}


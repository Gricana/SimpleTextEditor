#include "mainwindow.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow), settingsDialog(new SettingsDialog)
{
    ui->setupUi(this);
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

    ui->action_New->setIcon(QIcon(":/actions/new"));
    ui->action_Open->setIcon(QIcon(":/actions/open"));
    ui->action_Save->setIcon(QIcon(":/actions/save"));
    ui->action_Exit->setIcon(QIcon(":/actions/exit"));
    ui->action_Undo->setIcon(QIcon(":/actions/undo"));
    ui->action_Redo->setIcon(QIcon(":/actions/redo"));
    ui->action_Select_all->setIcon(QIcon(":/actions/select_all"));
    ui->action_Copy->setIcon(QIcon(":/actions/copy"));
    ui->action_Paste->setIcon(QIcon(":/actions/paste"));
    ui->action_Cut->setIcon(QIcon(":/actions/cut"));
    ui->action_About_Qt->setIcon(QIcon(":/actions/about_qt"));
    ui->action_About_program->setIcon(QIcon(":/actions/about_program"));
    ui->action_Settings->setIcon(QIcon(":/actions/settings"));

    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(slotNew()), Qt::UniqueConnection);
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(slotNew()), Qt::UniqueConnection);
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(slotOpen()), Qt::UniqueConnection);
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(ui->action_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()), Qt::UniqueConnection);
    connect(ui->action_About_program, SIGNAL(triggered()), this, SLOT(slotAboutProgram()), Qt::UniqueConnection);
    connect(ui->action_Settings, SIGNAL(triggered()), settingsDialog, SLOT(show())); // adding connecting for setting with method showPreferencesDialog()
    slotNew();
}

void MainWindow::showPreferencesDialog()
{
    settingsDialog->show();
}

void MainWindow::updateTitle()
{
    QString title = QString("TextEditor - %1[*]").arg(fileName);
    setWindowTitle(title);
}

void MainWindow::slotNew()
{
    fileName = "UntitledFile";
    ui->plainTextEdit->clear();
    setWindowModified(false);
    updateTitle();
}

void MainWindow::slotOpen()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Open file . . . ", QDir::homePath(), "Text files (*.txt)::All files (*.*)");
    if (fileName.isEmpty()) { return; }
    if (!askForFileSaveAndClose()){ return; }
    QFile file(fileName);
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

MainWindow::~MainWindow()
{
    delete ui;
}


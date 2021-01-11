#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QTranslator>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

void SettingsDialog::setRussianLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_ru").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void SettingsDialog::setEnglishLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_en").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

bool SettingsDialog::isShowToolBar() const
{
    return ui->showToolBarCheckBox->isChecked();
}

void SettingsDialog::setShowToolBar(bool show)
{
    ui->showToolBarCheckBox->setChecked(show);
}

bool SettingsDialog::isShowStatusBar() const
{
    return ui->showStatusBarCheckBox->isChecked();
}

void SettingsDialog::setShowStatusBar(bool show)
{
    ui->showStatusBarCheckBox->setChecked(show);
}

bool SettingsDialog::isThemeLight() const
{
    return ui->radioButton_Light->isChecked();
}

bool SettingsDialog::isThemeDark() const
{
    return ui->radioButton_Dark->isChecked();
}
bool SettingsDialog::isWordWrap() const
{
    return ui->checkBox_word_wrap->isChecked();
}

void SettingsDialog::setLightTheme(bool check)
{
    ui->radioButton_Light->setChecked(check);
}

void SettingsDialog::setDarkTheme(bool check)
{
    ui->radioButton_Dark->setChecked(check);
}

void SettingsDialog::setWordWrap(bool check)
{
    ui->checkBox_word_wrap->setChecked(check);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

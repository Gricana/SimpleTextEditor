#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
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

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

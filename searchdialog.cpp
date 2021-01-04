#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

QString SearchDialog::getText()
{
    return ui->lineEdit_text->text();
}

bool SearchDialog::isCaseSensitive()
{
    return ui->checkBox->isChecked();
}

void SearchDialog::setCaseSensitive(bool set)
{
    ui->checkBox->setChecked(set);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

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
    return ui->lineEdit_text_12->text();
}

bool SearchDialog::isCaseSensitive()
{
    return ui->checkBox_23->isChecked();
}

bool SearchDialog::isFirstOccurrence()
{
    return ui->radioButton_67->isChecked();;
}

bool SearchDialog::isAllFollowingOccurrences()
{
    return ui->radioButton_69->isChecked();
}

bool SearchDialog::isAllDocument()
{
    return ui->radioButton_68->isChecked();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

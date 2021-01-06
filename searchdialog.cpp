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

bool SearchDialog::isFirstOccurrence()
{
    return ui->radioButton_2->isChecked();;
}

bool SearchDialog::isAllFollowingOccurrences()
{
    return ui->radioButton->isChecked();
}

bool SearchDialog::isAllDocument()
{
    return ui->radioButton_3->isChecked();
}

bool SearchDialog::isCaseSensitiveReplace()
{
    return ui->checkBox_4->isChecked();
}

bool SearchDialog::isFirstOccurenceReplace()
{
    return ui->radioButton_10->isChecked();
}

bool SearchDialog::isAllFollowingReplace()
{
    return ui->radioButton_11->isChecked();
}

bool SearchDialog::isAllDocumentReplace()
{
    return ui->radioButton_12->isChecked();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

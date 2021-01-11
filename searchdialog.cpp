#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QTranslator>

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

void SearchDialog::setRussianLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_ru").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void SearchDialog::setEnglishLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_en").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
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

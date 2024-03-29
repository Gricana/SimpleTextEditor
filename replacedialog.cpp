#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QTranslator>

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
}

void ReplaceDialog::setRussianLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_ru").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void ReplaceDialog::setEnglishLanguage()
{
    QTranslator translator;
    translator.load(QString("%1/languages/QReader_en").arg(QCoreApplication::applicationDirPath()));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

QString ReplaceDialog::getTextReplaced()
{
    return ui->lineEdit_text_12->text();
}

QString ReplaceDialog::getTextReplacing()
{
    return ui->lineEdit_text_13->text();
}

bool ReplaceDialog::isCaseSensitiveReplace()
{
    return ui->checkBox_23->isChecked();
}

bool ReplaceDialog::isFirstOccurrenceReplace()
{
    return ui->radioButton_67->isChecked();
}

bool ReplaceDialog::isAllFollowingReplace()
{
    return ui->radioButton_69->isChecked();
}

bool ReplaceDialog::isAllDocumentReplace()
{
    return ui->radioButton_68->isChecked();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

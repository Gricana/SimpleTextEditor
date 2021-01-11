#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();
    QString getText();
    bool isCaseSensitive();
    bool isFirstOccurrence();
    bool isAllFollowingOccurrences();
    bool isAllDocument();
    void setRussianLanguage();
    void setEnglishLanguage();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H

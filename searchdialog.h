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
    QString getTextReplaced();
    QString getTextReplacing();
    bool isCaseSensitive();
    bool isFirstOccurrence();
    bool isAllFollowingOccurrences();
    bool isAllDocument();
    bool isFirstOccurenceReplace();
    bool isAllFollowingReplace();
    bool isAllDocumentReplace();
    bool isCaseSensitiveReplace();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H

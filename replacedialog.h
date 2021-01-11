#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();
    QString getTextReplaced();
    QString getTextReplacing();
    bool isFirstOccurrenceReplace();
    bool isAllFollowingReplace();
    bool isAllDocumentReplace();
    bool isCaseSensitiveReplace();
    void setRussianLanguage();
    void setEnglishLanguage();

private:
    Ui::ReplaceDialog *ui;
};

#endif // REPLACEDIALOG_H

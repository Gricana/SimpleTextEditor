#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    bool isShowToolBar() const;
    void setShowToolBar(bool show);
    bool isShowStatusBar() const;
    void setShowStatusBar(bool show);
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H

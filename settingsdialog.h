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
    bool isThemeLight() const;
    bool isThemeDark() const;
    bool isWordWrap() const;
    void setLightTheme(bool check);
    void setDarkTheme(bool check);
    void setWordWrap(bool check);
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPrinter>
#include <QSettings>
class SettingsDialog;
class SearchDialog;
class ReplaceDialog;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString fileName;
    int app_counter;
    QFont font = QFont("Times", 14);
    QColor color;
    bool isLight, isDark;
    bool isReplace;
    unsigned long int zoomValue = 100;
    void lightTheme();
    void darkTheme();
    void updateTitle();
    bool askForFileSaveAndClose();
    SettingsDialog *settingsDialog;
    SearchDialog *searchDialog;
    ReplaceDialog *replaceDialog;
    QSettings settings;
    void readSettings();
    void writeSettings();
    void applyInputSettings();
    void checkingReplace();
    void setLanguageSetting();
    void applyLanguageSetting();
private slots:
    void slotNew();
    void slotOpen();
    void slotSave();
    void slotPreview();
    void slotPrint();
    void closeEvent(QCloseEvent*);
    void slotAboutProgram();
    void showPreferencesDialog();
    void slotPreferencesAccepted();
    void slotOutNumberStringAndColumn();
    void slotShowDateAndTime();
    void slotGoToTheLine();
    void slotSetFont();
    void slotSetColorText();
    void slotSetColorBackground();
    void slotZoomIn();
    void slotZoomOut();
    void slotDefaultZoom();
    void printPreview(QPrinter*);
    void showSearchDialog();
    void showReplaceDialog();
    void slotFindText();
    void slotReplaceText();
    void slotRussianLanguage();
    void slotEnglishLanguage();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
class SettingsDialog;

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
    bool isDark = true, isLight = false;
    QFont font;
    unsigned long int zoomValue = 100;
    void lightTheme();
    void darkTheme();
    void updateTitle();
    bool askForFileSaveAndClose();
    SettingsDialog *settingsDialog;
    void readSettings();
    void writeSettings();
    void applySettings();
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
};
#endif // MAINWINDOW_H

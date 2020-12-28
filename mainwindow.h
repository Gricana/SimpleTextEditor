#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void updateTitle();
    bool askForFileSaveAndClose();
    SettingsDialog *settingsDialog;
private slots:
    void slotNew();
    void slotOpen();
    void slotSave();
    void slotAboutProgram();
    void showPreferencesDialog();
};
#endif // MAINWINDOW_H

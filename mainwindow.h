#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlistwidget.h>

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

private slots:
    void on_listTasks_itemDoubleClicked(QListWidgetItem *item);

    void on_btnRemoveSelectedTasks_clicked();

    void on_btnRemoveAllTasks_clicked();

    void on_btnAddTask_clicked();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
    const QString windowBaseTitle = "#TODO";
    QString currentFilePath;

    void updateWindowTitle(const QString &secondaryTitle);

    void resetWindow();

    bool saveTasksToFile(const QString &filePath);
    bool loadTasksFromFile(const QString &filePath);
};
#endif // MAINWINDOW_H

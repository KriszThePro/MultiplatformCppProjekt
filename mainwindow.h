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

private:
    Ui::MainWindow *ui;
    const QString windowBaseTitle = "#TODO";

    void updateWindowTitle(const QString &secondaryTitle);
};
#endif // MAINWINDOW_H

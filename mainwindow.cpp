#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "edititemdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->updateWindowTitle("Untitled");

    ui->listTasks->addItem("item1");
    ui->listTasks->addItem("item2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWindowTitle(const QString &secondaryTitle)
{
    QString newTitle = (
        secondaryTitle.isNull() || secondaryTitle.isEmpty()
            ? this->windowBaseTitle
            : secondaryTitle + " - " + this->windowBaseTitle
    );
    this->setWindowTitle(newTitle);
}

void MainWindow::on_listTasks_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    EditItemDialog dialog(item);
    if (dialog.exec() == QDialog::Accepted) {
        item->setText(dialog.editedText());
    }
}

void MainWindow::on_btnRemoveSelectedTasks_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->listTasks->selectedItems();
    for (QListWidgetItem* item : std::as_const(selectedItems)) {
        delete ui->listTasks->takeItem(ui->listTasks->row(item));
    }
}

void MainWindow::on_btnRemoveAllTasks_clicked()
{
    int ret = QMessageBox::question(
        this,
        "Remove All Items",
        "Are you sure you want to remove all the items from the list?",
        QMessageBox::Ok | QMessageBox::Cancel,
        QMessageBox::Ok
    );

    if (QMessageBox::Cancel == ret) {
        return;
    }

    QList<QListWidgetItem*> allItems;
    for (int i = 0; i < ui->listTasks->count(); ++i) {
        allItems.append(ui->listTasks->item(i));
    }
    for (QListWidgetItem* item : std::as_const(allItems)) {
        delete ui->listTasks->takeItem(ui->listTasks->row(item));
    }
}


void MainWindow::on_btnAddTask_clicked()
{
    QString taskText = ui->textNewTask->text();

    if (taskText.isNull() || taskText.isEmpty()) {
        return;
    }

    ui->textNewTask->setText("");
    ui->listTasks->addItem(taskText);
}


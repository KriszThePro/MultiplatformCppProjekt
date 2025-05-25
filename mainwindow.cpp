#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "edititemdialog.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resetWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWindowTitle(const QString &secondaryTitle)
{
    QString newTitle = (secondaryTitle.isNull() || secondaryTitle.isEmpty() ? "Untitled" : secondaryTitle) + " - " + this->windowBaseTitle;
    this->setWindowTitle(newTitle);
}

void MainWindow::resetWindow()
{
    this->updateWindowTitle(nullptr);
    this->currentFilePath.clear();
    ui->textNewTask->clear();
    ui->listTasks->clear();
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
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    if (QMessageBox::No == ret) {
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

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

bool MainWindow::saveTasksToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Save Error", "Could not open file for writing.");
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < ui->listTasks->count(); ++i) {
        out << ui->listTasks->item(i)->text() << "\n";
    }

    file.close();
    this->currentFilePath = filePath;
    this->updateWindowTitle(filePath);
    return true;
}

bool MainWindow::loadTasksFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Load Error", "Could not open file for reading.");

        if (this->currentFilePath.isNull() || this->currentFilePath.isEmpty()) {
            this->updateWindowTitle(nullptr);
        }

        return false;
    }

    ui->textNewTask->clear();
    ui->listTasks->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            ui->listTasks->addItem(line);
        }
    }

    file.close();
    this->currentFilePath = filePath;
    this->updateWindowTitle(filePath);
    return true;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Tasks File", "", "Text Files (*.txt);;All Files (*)");
    if (!filePath.isEmpty()) {
        loadTasksFromFile(filePath);
    }
    else {
        QMessageBox::information(this, "Open File", "No file selected.");
    }
}

void MainWindow::on_actionNew_triggered()
{
    int ret = QMessageBox::question(
        this,
        "New Tasks",
        "Are you sure you want to create a new task list? Unsaved changes will be lost.",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    if (ret == QMessageBox::No) {
        return;
    }

    this->resetWindow();
}

void MainWindow::on_actionSave_triggered()
{
    if (this->currentFilePath.isNull() || this->currentFilePath.isEmpty()) {
        QString filePath = QFileDialog::getSaveFileName(this, "Save Tasks File", "", "Text Files (*.txt);;All Files (*)");
        if (filePath.isEmpty()) {
            return;
        }
        this->currentFilePath = filePath;
    }

    this->saveTasksToFile(this->currentFilePath);
}


void MainWindow::on_actionSave_As_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Tasks File As", "", "Text Files (*.txt);;All Files (*)");
    if (filePath.isEmpty()) {
        return;
    }
    this->saveTasksToFile(filePath);
}


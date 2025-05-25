#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>

class QLineEdit;
class QListWidgetItem;

class EditItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditItemDialog(QListWidgetItem *item, QWidget *parent = nullptr);
    QString editedText() const;

private:
    QLineEdit *lineEdit;
    QListWidgetItem *itemPtr;
};

#endif // EDITITEMDIALOG_H

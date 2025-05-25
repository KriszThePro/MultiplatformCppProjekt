#include "EditItemDialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QListWidgetItem>

EditItemDialog::EditItemDialog(QListWidgetItem *item, QWidget *parent)
    : QDialog(parent), itemPtr(item)
{
    setWindowTitle("Edit Item");

    lineEdit = new QLineEdit(this);
    lineEdit->setText(item->text());
    lineEdit->selectAll();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditItemDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditItemDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

QString EditItemDialog::editedText() const
{
    return lineEdit->text();
}

#include <tabnamedialog.hpp>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

TabNameDialog::TabNameDialog(QWidget* parent, bool rename) : QDialog(parent) {
    setModal(true);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QLabel* label;

    if (rename) {
        setWindowTitle("Rename Tab");
        label = new QLabel("Enter a new name for the tab:");
    } else {
        setWindowTitle("Add New Tab");
        label = new QLabel("Enter a name for the new tab:");
    }

    mainLayout->addWidget(label);

    m_nameEdit = new QLineEdit();
    mainLayout->addWidget(m_nameEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QObject::connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    m_nameEdit->setFocus();
}

QString TabNameDialog::getName() const {
    return m_nameEdit->text();
}

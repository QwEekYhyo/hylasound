#include <tabnamedialog.hpp>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

TabNameDialog::TabNameDialog(QWidget* parent, bool rename) : QDialog(parent) {
    setModal(true);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QLabel* label;

    if (rename) {
        setWindowTitle(tr("Rename Tab"));
        label = new QLabel(tr("Enter a new name for the tab:"));
    } else {
        setWindowTitle(tr("Add New Tab"));
        label = new QLabel(tr("Enter a name for the new tab:"));
    }

    mainLayout->addWidget(label);

    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText(tr("Tab name"));
    mainLayout->addWidget(m_nameEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    QPushButton* okButton = new QPushButton(tr("OK"));
    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QObject::connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    m_nameEdit->setFocus();
}

QString TabNameDialog::getName() const {
    return m_nameEdit->text();
}

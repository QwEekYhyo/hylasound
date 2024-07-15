#pragma once

#include <QDialog>
#include <QLineEdit>

class TabNameDialog final : public QDialog {
    Q_OBJECT

public:
    // this class is used both to add a new tab and to rename an
    // existing tab, arg rename is used to differenciate cases
    TabNameDialog(QWidget* parent = nullptr, bool rename = false);
    QString getName() const;

private:
    QLineEdit* m_nameEdit;

};

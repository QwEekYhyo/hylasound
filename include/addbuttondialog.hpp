#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class AddButtonDialog final : public QDialog {
    Q_OBJECT

public:
    AddButtonDialog(QWidget* parent = nullptr);
    QString getName() const;
    QString getFilePath() const;

private slots:
    void browseFile();

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_filePathEdit;
    QPushButton* m_browseButton;
    QString m_filePath;

};

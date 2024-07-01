#pragma once

#include <QDialog>
#include <QLabel>

class FileNotFoundDialog final : public QDialog {
    Q_OBJECT

public:
    enum class Result {
        Dismiss,
        Delete,
        Browse
    };

    FileNotFoundDialog(const QString& filePath, QWidget* parent = nullptr);

    inline Result getResult() const;
    inline QString getNewFilePath() const;

private slots:
    void onDismissClicked();
    void onDeleteClicked();
    void onBrowseClicked();

private:
    Result m_result;
    QString m_faultyFilePath;
    QString m_newFilePath;

};

FileNotFoundDialog::Result FileNotFoundDialog::getResult() const {
    return m_result;
}

QString FileNotFoundDialog::getNewFilePath() const {
    return m_newFilePath;
}

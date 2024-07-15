#pragma once

#include <soundbutton.hpp>

#include <QList>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QJsonArray>

class ButtonGrid : public QWidget {
    Q_OBJECT

public:
    ButtonGrid(QMediaPlayer* player, QString jsonSaveFilePath, QWidget* parent = nullptr);

    bool addButton(const QString& name, const QString& filepath, bool doSave = true);

public slots:
    void clearAllButtons();

private slots:
    void removeButton(SoundButton* button, bool doSave = true);
    void onFileNotFound(SoundButton* button);

private:
    static const size_t MAX_COLUMN;

    QString m_saveFilePath;
    size_t m_cursor{0};
    QList<SoundButton*> m_buttons;
    QGridLayout* m_layout;

    void saveButtonsToJson();
    void writeJsonFile(const QJsonArray& jsonArray);
    void loadButtonsFromJson();
    QJsonArray readJsonFile();

};

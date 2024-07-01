#pragma once

#include <soundbutton.hpp>

#include <QList>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QJsonArray>

class ButtonGrid : public QWidget {
    Q_OBJECT

public:
    ButtonGrid(QMediaPlayer* player, QWidget* parent = nullptr);

    void addButton(const QString& name, const QString& filepath);

private slots:
    void removeButton(SoundButton* button);
    void onFileNotFound(SoundButton* button);

private:
    static const QString JSON_SAVE_FILE;
    static const size_t MAX_COLUMN;

    QList<SoundButton*> m_buttons;
    QGridLayout* m_layout;
    QMediaPlayer* m_player;

    void saveButtonsToJson();
    void writeJsonFile(const QJsonArray& jsonArray);
    void loadButtonsFromJson();
    QJsonArray readJsonFile();

};

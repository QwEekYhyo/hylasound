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

public slots:
    void clearAllButtons();

private slots:
    void removeButton(SoundButton* button);
    void onFileNotFound(SoundButton* button);

private:
    static const QString JSON_SAVE_FILE;
    static const size_t MAX_COLUMN;

    size_t m_cursor{0};
    QList<SoundButton*> m_buttons;
    QGridLayout* m_layout;

    void saveButtonsToJson();
    void writeJsonFile(const QJsonArray& jsonArray);
    void loadButtonsFromJson();
    QJsonArray readJsonFile();

};

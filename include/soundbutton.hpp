#pragma once

#include <QPushButton>
#include <QMediaPlayer>

class SoundButton : public QPushButton {
    Q_OBJECT

public:
    SoundButton(QWidget* parent = nullptr);
    SoundButton(QMediaPlayer* player, QWidget* parent = nullptr);
    SoundButton(const QString& name, const QString& path, QMediaPlayer* player, QWidget* parent = nullptr);
    SoundButton(const SoundButton& other);

    inline void setPlayer(QMediaPlayer* player);
    inline void setDisplayName(const QString& name);
    inline void setSoundPath(const QString& path);

    SoundButton& operator=(const SoundButton& other);

private:
    QMediaPlayer* m_player = nullptr;
    QString m_path;
};

void SoundButton::setPlayer(QMediaPlayer* player) {
    m_player = player;
}

void SoundButton::setDisplayName(const QString& name) {
    setText(name);
}

void SoundButton::setSoundPath(const QString& path) {
    m_path = path;
}

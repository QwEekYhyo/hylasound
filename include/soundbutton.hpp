#pragma once

#include <QPushButton>
#include <QMediaPlayer>
#include <QMenu>

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
    inline const QString& getSoundPath();

    SoundButton& operator=(const SoundButton& other);

signals:
    void removeRequested(SoundButton* button);
    void fileNotFound(SoundButton* button);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    void renameButton();

private:
    QMediaPlayer* m_player = nullptr;
    QString m_path;
    QMenu* m_contextMenu;

    void createContextMenu();

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

const QString& SoundButton::getSoundPath() {
    return m_path;
}

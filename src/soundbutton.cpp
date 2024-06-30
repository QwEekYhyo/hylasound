#include <soundbutton.hpp>

SoundButton::SoundButton(QWidget* parent) : QPushButton(parent) {
    connect(this, &QPushButton::released, this, [&](){
        if (m_player && !m_path.isEmpty()) {
#ifdef Q_OS_WIN
            if (QString::compare(m_path, m_player->source().path(), Qt::CaseInsensitive) != 0) {
#else
            if (QString::compare(m_path, m_player->source().path(), Qt::CaseSensitive) != 0) {
#endif
                m_player->setSource(QUrl::fromLocalFile(m_path));
            }
            m_player->play();
        }
    });
}

SoundButton::SoundButton(QMediaPlayer* player, QWidget* parent) : SoundButton(parent) {
    setPlayer(player);
}

SoundButton::SoundButton(const QString& name, const QString& path, QMediaPlayer* player, QWidget* parent) : SoundButton(player, parent) {
    setDisplayName(name);
    setSoundPath(path);
}

#include <soundbutton.hpp>

#include <QInputDialog>
#include <QLineEdit>
#include <QContextMenuEvent>
#include <QFile>

SoundButton::SoundButton(QWidget* parent) : QPushButton(parent) {
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(this, &QPushButton::released, this, [&](){
        if (m_player && !m_path.isEmpty()) {
            if (!QFile::exists(m_path)) {
                emit fileNotFound(this);
                return;
            }
            m_player->setSource(QUrl::fromLocalFile(m_path));
            m_player->play();
        }
    });

    createContextMenu();
}

SoundButton::SoundButton(QMediaPlayer* player, QWidget* parent) : SoundButton(parent) {
    setPlayer(player);
}

SoundButton::SoundButton(const QString& name, const QString& path, QMediaPlayer* player, QWidget* parent) : SoundButton(player, parent) {
    setDisplayName(name);
    setSoundPath(path);
}

SoundButton::SoundButton(const SoundButton& other) : SoundButton() {
    operator=(other);
}

SoundButton& SoundButton::operator=(const SoundButton& other) {
    if (this != &other) {
        setPlayer(other.m_player);
        setDisplayName(other.text());
        setSoundPath(other.m_path);
    }

    return *this;
}

void SoundButton::createContextMenu() {
    m_contextMenu = new QMenu(this);
    QAction* renameAction = m_contextMenu->addAction("&Rename");
    QAction* removeAction = m_contextMenu->addAction("&Delete");

    connect(renameAction, &QAction::triggered, this, &SoundButton::renameButton);
    connect(removeAction, &QAction::triggered, this, [this]() {
        emit removeRequested(this, true);
    });
}

void SoundButton::contextMenuEvent(QContextMenuEvent* event) {
    m_contextMenu->exec(event->globalPos());
}

void SoundButton::renameButton() {
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Button", "Enter new name:", QLineEdit::Normal, text(), &ok);
    if (ok && !newName.isEmpty()) {
        setDisplayName(newName);
    }
}

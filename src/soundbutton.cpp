#include <soundbutton.hpp>
#include <globalstyle.hpp>

#include <QInputDialog>
#include <QLineEdit>
#include <QContextMenuEvent>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QPainterPath>
#include <QSettings>

SoundButton::SoundButton(QWidget* parent) : QPushButton(parent) {
    QFont font = QPushButton::font();
    font.setPointSize(20);
    setFont(font);

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

void SoundButton::renameButton() {
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Button", "Enter new name:", QLineEdit::Normal, text(), &ok);
    if (ok && !newName.isEmpty()) {
        setDisplayName(newName);
    }
}

void SoundButton::createContextMenu() {
    m_contextMenu = new QMenu(this);
    QAction* renameAction = m_contextMenu->addAction("&Rename Button");
    QAction* removeAction = m_contextMenu->addAction("&Remove Button");

    connect(renameAction, &QAction::triggered, this, &SoundButton::renameButton);
    connect(removeAction, &QAction::triggered, this, [this]() {
        emit removeRequested(this, true);
    });
}

void SoundButton::contextMenuEvent(QContextMenuEvent* event) {
    m_contextMenu->exec(event->globalPos());
}

void SoundButton::enterEvent(QEnterEvent* event) {
    if (isEnabled()) {
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
        effect->setOpacity(0.7);
        setGraphicsEffect(effect);
    }
    QPushButton::enterEvent(event);
}

void SoundButton::leaveEvent(QEvent* event) {
    setGraphicsEffect(nullptr);
    QPushButton::leaveEvent(event);
}

// This method is called a hundred times per second I don't know if
// all this logic being spammed is good practice but whatever
void SoundButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);
    QSettings settings;
    QString storedStyle = settings.value("globalstyle", "none").toString();

    if (GlobalStyle::fromString(storedStyle) == GlobalStyle::AWESOME) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);

        QFont font = this->font();
        painter.setFont(font);

        QString text = this->text();
        QRect rect = this->rect();

        QFontMetrics fm(font);
        int x = (rect.width() - fm.horizontalAdvance(text)) / 2;
        int y = (rect.height() + fm.ascent() - fm.descent()) / 2;

        QPainterPath path;
        path.addText(x, y, font, text);

        // Draw the stroke
        QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawPath(path);

        // Draw the fill
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#ffabd2"));
        painter.drawPath(path);
    }
}

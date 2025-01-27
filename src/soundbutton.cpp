#include <soundbutton.hpp>
#include <globalstyle.hpp>

#include <QInputDialog>
#include <QLineEdit>
#include <QContextMenuEvent>
#include <QFile>
#include <QGraphicsColorizeEffect>
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
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Rename Button"));
    dialog.setLabelText(tr("Enter new name:"));
    dialog.setTextValue(text());
    dialog.setTextEchoMode(QLineEdit::Normal);

    QLineEdit *lineEdit = dialog.findChild<QLineEdit*>();
    if (lineEdit) {
        lineEdit->setMaxLength(25);
    }

    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.textValue();
        if (!newName.isEmpty()) {
            setDisplayName(newName);
            emit changedButtonName();
        }
    }
}

void SoundButton::createContextMenu() {
    m_contextMenu = new QMenu(this);
    QAction* renameAction = m_contextMenu->addAction(tr("Re&name Button"));
    QAction* removeAction = m_contextMenu->addAction(tr("&Remove Button"));

    connect(renameAction, &QAction::triggered, this, &SoundButton::renameButton);
    connect(removeAction, &QAction::triggered, this, [this]() {
        emit removeRequested(this, true);
    });
}

void SoundButton::contextMenuEvent(QContextMenuEvent* event) {
    m_contextMenu->exec(event->globalPos());
}

void SoundButton::enterEvent(QEnterEvent* event) {
    if (isEnabled() && m_isAwesomeStyled) {
        QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(this);
        effect->setColor(Qt::white);
        effect->setStrength(0.2);
        setGraphicsEffect(effect);
    }
    QPushButton::enterEvent(event);
}

void SoundButton::leaveEvent(QEvent* event) {
    setGraphicsEffect(nullptr);
    QPushButton::leaveEvent(event);
}

void SoundButton::mousePressEvent(QMouseEvent* event) {
    if (isEnabled() && m_isAwesomeStyled) {
        QGraphicsColorizeEffect* effect = (QGraphicsColorizeEffect*) this->graphicsEffect();
        effect->setStrength(0.4);
    }
    QPushButton::mousePressEvent(event);
}

void SoundButton::mouseReleaseEvent(QMouseEvent* event) {
    if (isEnabled() && m_isAwesomeStyled) {
        QGraphicsColorizeEffect* effect = (QGraphicsColorizeEffect*) this->graphicsEffect();
        effect->setStrength(0.2);
    }
    QPushButton::mouseReleaseEvent(event);
}

// This method is called a hundred times per second I don't know if
// all this logic being spammed is good practice but whatever
void SoundButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);
    QSettings settings;
    QString storedStyle = settings.value("globalstyle", "none").toString();
    m_isAwesomeStyled = GlobalStyle::fromString(storedStyle) == GlobalStyle::AWESOME;

    if (m_isAwesomeStyled) {
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

#include <buttongrid.hpp>

ButtonGrid::ButtonGrid(QMediaPlayer* player, QWidget* parent) : QWidget(parent) {
    m_player = player;
    m_layout = new QGridLayout(this);
    m_buttons.reserve(50);
}

void ButtonGrid::addButton(const QString& name, const QString& filepath) {
    SoundButton* button = new SoundButton(name, filepath, m_player, this);
    m_buttons.append(button);
    int row = (m_buttons.size() - 1) / 10;
    int column = (m_buttons.size() - 1) % 10;
    m_layout->addWidget(button, row, column);
}

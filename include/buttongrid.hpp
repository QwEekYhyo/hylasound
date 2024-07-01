#pragma once

#include <soundbutton.hpp>

#include <QList>
#include <QGridLayout>
#include <QMediaPlayer>

class ButtonGrid : public QWidget {
    Q_OBJECT

public:
    ButtonGrid(QMediaPlayer* player, QWidget* parent = nullptr);

    void addButton(const QString& name, const QString& filepath);

private slots:
    void removeButton(SoundButton* button);

private:
    QList<SoundButton*> m_buttons;
    QGridLayout* m_layout;
    QMediaPlayer* m_player;

};

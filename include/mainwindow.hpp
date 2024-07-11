#pragma once

#include <buttongrid.hpp>

#include <QMainWindow>
#include <QMediaPlayer>
#include <QSettings>

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openAddButtonDialog();

private:
    QSettings m_settings;
    ButtonGrid* m_mainWidget;
    QMediaPlayer* m_player;

    void setupMenuBar();

};

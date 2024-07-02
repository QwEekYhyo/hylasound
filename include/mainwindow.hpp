#pragma once

#include <buttongrid.hpp>

#include <QMainWindow>
#include <QMediaPlayer>

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openAddButtonDialog();

private:
    ButtonGrid* m_mainWidget;
    QMediaPlayer* m_player;

    void setupMenuBar();

};

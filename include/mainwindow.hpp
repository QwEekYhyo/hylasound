#pragma once

#include <gridtabs.hpp>

#include <QMainWindow>
#include <QSettings>

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    QString openNewTabDialog();

private slots:
    void openAddButtonDialog();

private:
    QSettings m_settings;
    GridTabs* m_mainWidget;

    void setupMenuBar();

};

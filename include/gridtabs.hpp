#pragma once

#include <buttongrid.hpp>

#include <QTabWidget>
#include <QMediaPlayer>

class GridTabs : public QTabWidget {
    Q_OBJECT

public:
    GridTabs(QWidget* parent = nullptr);

    ButtonGrid* currentGrid() const;
    void addGrid(const QString& name);

private:
    QString m_saveDirectory;
    QMediaPlayer* m_player;

    void addEmptyTab();
    void contextMenuEvent(QContextMenuEvent* event) override;
    QMenu* createContextMenu(int tabIndex);

};

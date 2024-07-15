#include <gridtabs.hpp>
#include <tabnamedialog.hpp>

#include <QDir>
#include <QCoreApplication>
#include <QAudioOutput>
#include <QTabBar>
#include <QContextMenuEvent>
#include <QMenu>

GridTabs::GridTabs(QWidget* parent) : QTabWidget(parent), m_saveDirectory(QCoreApplication::applicationDirPath() + "/saves") {
    m_player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    m_player->setAudioOutput(audioOutput);

    QDir dir(m_saveDirectory);
    if (!dir.exists())
        dir.mkpath(".");

    for (QString file : dir.entryList(QStringList() << "*.json", QDir::Files)) {
        addGrid(file.split('.')[0]);
    }
    if (count() == 0)
        addGrid("New tab");
}

ButtonGrid* GridTabs::currentGrid() const {
    return (ButtonGrid*) currentWidget();
}

void GridTabs::addGrid(const QString& name) {
    ButtonGrid* grid = new ButtonGrid(m_player, m_saveDirectory + '/' + name + ".json", this);
    addTab(grid, name);
}

void GridTabs::contextMenuEvent(QContextMenuEvent* event) {
    int tabIndex = tabBar()->tabAt(event->pos());
    if (tabIndex != -1) {
        QMenu* menu = createContextMenu(tabIndex);
        menu->exec(event->globalPos());
        delete menu;
    }
}

QMenu* GridTabs::createContextMenu(int tabIndex) {
    QMenu* menu = new QMenu(this);

    QAction* renameAction = menu->addAction("Rename Tab");
    connect(renameAction, &QAction::triggered, this, [this, tabIndex]() {
        ButtonGrid* toRename = (ButtonGrid*) widget(tabIndex);
        TabNameDialog dialog(this, true);
        if (dialog.exec() == QDialog::Accepted) {
            QString newName = dialog.getName().trimmed();
            if (!newName.isEmpty()) {
                setTabText(tabIndex, newName);
                QFile saveFile(toRename->getSaveFilePath());
                toRename->setSaveFilePath(m_saveDirectory + '/' + newName + ".json");
                saveFile.rename(toRename->getSaveFilePath());
            }
        }
    });

    QAction* removeAction = menu->addAction("Remove Tab");
    connect(removeAction, &QAction::triggered, this, [this, tabIndex]() {
        ButtonGrid* toDelete = (ButtonGrid*) widget(tabIndex);
        QFile saveFile(toDelete->getSaveFilePath());
        saveFile.remove();
        removeTab(tabIndex);
        toDelete->deleteLater();
    });

    return menu;
}

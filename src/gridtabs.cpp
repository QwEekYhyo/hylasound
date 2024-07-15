#include <gridtabs.hpp>

#include <QDir>
#include <QCoreApplication>
#include <QAudioOutput>

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

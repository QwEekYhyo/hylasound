#include <mainwindow.hpp>
#include <buttongrid.hpp>

#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGridLayout>
#include <QList>

MainWindow::MainWindow() {
    setWindowTitle("Camille SoundBoard");
    resize(1280, 720);

    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    ButtonGrid* mainWidget = new ButtonGrid(player);
    mainWidget->addButton("test", "/home/logan/Music/test.mp3");
    mainWidget->addButton("another test", "/home/logan/Music/test2.mp3");

    setCentralWidget(mainWidget);
}

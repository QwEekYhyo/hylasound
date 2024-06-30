#include <mainwindow.hpp>
#include <soundbutton.hpp>

#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGridLayout>

MainWindow::MainWindow() {
    setWindowTitle("Camille SoundBoard");
    resize(1280, 720);

    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    QGridLayout* mainLayout = new QGridLayout;

    SoundButton* button = new SoundButton("test", "/home/logan/Music/test.mp3", player, this);
    mainLayout->addWidget(button, 0, 0);
    SoundButton* anotherButton = new SoundButton("another test", "/home/logan/Music/test2.mp3", player, this);
    mainLayout->addWidget(anotherButton, 0, 1);

    auto test = new QLabel("Placeholder", this);
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    test->setAutoFillBackground(true);
    test->setPalette(pal);

    mainLayout->addWidget(test, 0, 2);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

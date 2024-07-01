#include <mainwindow.hpp>
#include <addbuttondialog.hpp>

#include <QLabel>
#include <QAudioOutput>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow() {
    setWindowTitle("Camille SoundBoard");
    resize(1280, 720);

    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    m_mainWidget = new ButtonGrid(player);
    /*
    m_mainWidget->addButton("test", "/home/logan/Music/test.mp3");
    m_mainWidget->addButton("another test", "/home/logan/Music/test2.mp3");
    */

    setCentralWidget(m_mainWidget);

    QMenu* fileMenu = menuBar()->addMenu("&File");
    QAction* openAction = fileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::openAddButtonDialog);
}

void MainWindow::openAddButtonDialog() {
    AddButtonDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString filePath = dialog.getFilePath();

        if (!name.isEmpty() && !filePath.isEmpty()) {
            m_mainWidget->addButton(name, filePath);
            QMessageBox::information(this, "Success", "Button added successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Name or file path is empty. Button not added.");
        }
    }
}

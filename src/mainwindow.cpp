#include <mainwindow.hpp>
#include <addbuttondialog.hpp>
#include <aboutdialog.hpp>

#include <QLabel>
#include <QAudioOutput>
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow() {
    setWindowTitle("Camille SoundBoard");
    resize(1280, 720);

    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    m_mainWidget = new ButtonGrid(player);

    setCentralWidget(m_mainWidget);

    setupMenuBar();
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

void MainWindow::setupMenuBar() {
    // File
    QMenu* fileMenu = menuBar()->addMenu("&File");
    QAction* openAction = fileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::openAddButtonDialog);

    fileMenu->addSeparator();

    QAction* clearAction = fileMenu->addAction("Delete all buttons");
    connect(clearAction, &QAction::triggered, m_mainWidget, &ButtonGrid::clearAllButtons);
    QAction* quitAction = fileMenu->addAction("&Quit");
    quitAction->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);

    // Help
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    QAction* aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, [this](){
        AboutDialog about(this);
        about.exec();
    });
    QAction* aboutQtAction = helpMenu->addAction("About &Qt");
    connect(aboutQtAction, &QAction::triggered, this, [this](){
        QMessageBox::aboutQt(this);
    });
}

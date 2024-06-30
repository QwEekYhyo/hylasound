#include <mainwindow.hpp>

#include <QLabel>

MainWindow::MainWindow() {
    setWindowTitle("Camille SoundBoard");
    resize(1280, 720);

    auto test = new QLabel("Placeholder", this);
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    test->setAutoFillBackground(true);
    test->setPalette(pal);

    setCentralWidget(test);
}

#include <mainwindow.hpp>

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
  
    QCoreApplication::setApplicationName("SoundBoard");
  
    MainWindow mainWindow;
    mainWindow.show();
  
    return app.exec();
}

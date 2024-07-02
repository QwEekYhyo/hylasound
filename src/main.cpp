#include <mainwindow.hpp>

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
  
    QCoreApplication::setApplicationName("HylaSound");
  
    MainWindow mainWindow;
    mainWindow.show();
  
    return app.exec();
}

#include <mainwindow.hpp>

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
  
    QCoreApplication::setApplicationName("HylaSound");
    QCoreApplication::setOrganizationName("LoganCorp");
    QCoreApplication::setOrganizationDomain("logancorp.com");
  
    MainWindow mainWindow;
    mainWindow.show();
  
    return app.exec();
}

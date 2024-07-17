#include <mainwindow.hpp>

#include <QApplication>
#include <QTranslator>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
  
    QCoreApplication::setApplicationName("HylaSound");
    QCoreApplication::setOrganizationName("LoganCorp");
    QCoreApplication::setOrganizationDomain("logancorp.com");

    QTranslator appTranslator;
    // Load translations
    Q_UNUSED(appTranslator.load("translations/hylasound_fr"));

    app.installTranslator(&appTranslator);
  
    MainWindow mainWindow;
    mainWindow.show();
  
    return app.exec();
}

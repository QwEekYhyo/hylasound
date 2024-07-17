#include <mainwindow.hpp>

#include <QApplication>
#include <QTranslator>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
  
    QCoreApplication::setApplicationName("HylaSound");
    QCoreApplication::setOrganizationName("LoganCorp");
    QCoreApplication::setOrganizationDomain("logancorp.com");

    QString translationDir = QCoreApplication::applicationDirPath() + "/translations";

    QTranslator translator;
    QString locale = QLocale::system().name(); // for example "en_US"
    locale.truncate(locale.lastIndexOf('_'));  // for example "en"

    QString translationFile = QString("hylasound_%1.qm").arg(locale);

    if (translator.load(translationFile, translationDir)) {
        app.installTranslator(&translator);
        qDebug() << "Loaded translation:" << translationFile;
    } else {
        qDebug() << "Failed to load translation:" << translationFile;
    }
  
    MainWindow mainWindow;
    mainWindow.show();
  
    return app.exec();
}

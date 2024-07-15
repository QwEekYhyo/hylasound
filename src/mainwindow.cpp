#include <mainwindow.hpp>
#include <addbuttondialog.hpp>
#include <tabnamedialog.hpp>
#include <aboutdialog.hpp>
#include <globalstyle.hpp>

#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>
#include <QFile>

MainWindow::MainWindow() {
    setWindowTitle("HylaSound");
    resize(1280, 720);
    setWindowIcon(QIcon(":/hylasound.png"));

    m_mainWidget = new GridTabs(this);
    setCentralWidget(m_mainWidget);

    setupMenuBar();
}

QString MainWindow::openNewTabDialog() {
    TabNameDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.getName().trimmed();
    } else {
        return QString();
    }
}

void MainWindow::openAddButtonDialog() {
    AddButtonDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName().trimmed();
        QString filePath = dialog.getFilePath();

        if (!name.isEmpty() && !filePath.isEmpty()) {
            if (m_mainWidget->currentGrid()->addButton(name, filePath))
                QMessageBox::information(this, "Success", "Button added successfully!");
            else
                QMessageBox::critical(this, "Error", "Grid is full. Button not added.");
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
    QAction* newTabAction = fileMenu->addAction("Add New &Tab");
    connect(newTabAction, &QAction::triggered, this, [this](){
        QString tabName = openNewTabDialog();
        if (!tabName.isEmpty())
            m_mainWidget->addGrid(tabName);
    });

    fileMenu->addSeparator();

    QAction* clearAction = fileMenu->addAction("Delete All Buttons");
    connect(clearAction, &QAction::triggered, m_mainWidget->currentGrid(), &ButtonGrid::clearAllButtons);
    QAction* quitAction = fileMenu->addAction("&Quit");
    quitAction->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);

    // Settings
    QMenu* settingsMenu = menuBar()->addMenu("&Settings");
    QAction* styleAction = settingsMenu->addAction("Awesome Style");
    styleAction->setCheckable(true);
    connect(styleAction, &QAction::triggered, this, [this](bool checked){
        if (checked) {
            QFile file(":/styles/awesome.qss");
            if (file.open(QIODeviceBase::ReadOnly)) {
                setStyleSheet(file.readAll());
                file.close();
                GlobalStyle newStyle = GlobalStyle::AWESOME;
                m_settings.setValue("globalstyle", newStyle.toString());
            }
        } else {
            setStyleSheet("");
            GlobalStyle newStyle = GlobalStyle::DEFAULT;
            m_settings.setValue("globalstyle", newStyle.toString());
        }
    });
    // Read style stored in app settings
    QString storedStyle = m_settings.value("globalstyle", "none").toString();
    if (GlobalStyle::fromString(storedStyle) == GlobalStyle::AWESOME)
        styleAction->trigger();

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

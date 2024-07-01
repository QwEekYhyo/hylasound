#include <filenotfounddialog.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

FileNotFoundDialog::FileNotFoundDialog(const QString& filePath, QWidget* parent)
    : QDialog(parent, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint), m_result(Result::Dismiss), m_faultyFilePath(filePath) {

    setWindowTitle("File Not Found");
    setModal(true);
    setFixedSize(minimumWidth(), 160);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QString text = QString("The file \"%1\" is missing.\r\n").arg(m_faultyFilePath)
        .append("It may have been moved, deleted or renamed.\r\n")
        .append("You can choose to delete the button or browse files to search the file's new location.\r\n")
        .append("What would you like to do?");

    QLabel* textLabel = new QLabel(text);
    mainLayout->addWidget(textLabel);
    mainLayout->addSpacing(20);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* dismissButton = new QPushButton("Dismiss");
    QPushButton* deleteButton = new QPushButton("Delete");
    QPushButton* browseButton = new QPushButton("Browse");

    buttonLayout->addWidget(dismissButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(browseButton);

    mainLayout->addLayout(buttonLayout);

    connect(dismissButton, &QPushButton::clicked, this, &FileNotFoundDialog::onDismissClicked);
    connect(deleteButton, &QPushButton::clicked, this, &FileNotFoundDialog::onDeleteClicked);
    connect(browseButton, &QPushButton::clicked, this, &FileNotFoundDialog::onBrowseClicked);
}

void FileNotFoundDialog::onDismissClicked() {
    m_result = Result::Dismiss;
    accept();
}

void FileNotFoundDialog::onDeleteClicked() {
    m_result = Result::Delete;
    accept();
}

void FileNotFoundDialog::onBrowseClicked() {
    QString newFilePath = QFileDialog::getOpenFileName(
            this,
            "Select New Sound File",
            m_faultyFilePath,
            "Audio Files (*.mp3 *.wav *.WAV *.avi *.bwf *.ogg *.aif *.aiff *.caf)"
    );
    if (!newFilePath.isEmpty()) {
        m_newFilePath = newFilePath;
        m_result = Result::Browse;
        accept();
    }
}

#include <addbuttondialog.hpp>

#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AddButtonDialog::AddButtonDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Add New Button");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Name input
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* nameLabel = new QLabel("Button Name:");
    m_nameEdit = new QLineEdit();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(m_nameEdit);
    mainLayout->addLayout(nameLayout);

    // File input
    QHBoxLayout* fileLayout = new QHBoxLayout();
    QLabel* fileLabel = new QLabel("Sound File:");
    m_filePathEdit = new QLineEdit();
    m_browseButton = new QPushButton("Browse");
    fileLayout->addWidget(fileLabel);
    fileLayout->addWidget(m_filePathEdit);
    fileLayout->addWidget(m_browseButton);
    mainLayout->addLayout(fileLayout);

    // OK and Cancel buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    mainLayout->addLayout(buttonLayout);

    connect(m_browseButton, &QPushButton::clicked, this, &AddButtonDialog::browseFile);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void AddButtonDialog::browseFile() {
    m_filePath = QFileDialog::getOpenFileName(
            this,
            "Select Sound File",
            "",
            "Audio Files (*.mp3 *.wav *.WAV *.avi *.bwf *.ogg *.aif *.aiff *.caf)"
    );
    m_filePathEdit->setText(m_filePath);
}

QString AddButtonDialog::getName() const {
    return m_nameEdit->text();
}

QString AddButtonDialog::getFilePath() const {
    return m_filePath;
}

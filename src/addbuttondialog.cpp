#include <addbuttondialog.hpp>

#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AddButtonDialog::AddButtonDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Add New Button"));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Name input
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* nameLabel = new QLabel(tr("Button Name:"));
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText(tr("Button name"));
    m_nameEdit->setMaxLength(25);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(m_nameEdit);
    mainLayout->addLayout(nameLayout);

    // File input
    QHBoxLayout* fileLayout = new QHBoxLayout();
    QLabel* fileLabel = new QLabel(tr("Sound File:"));
    m_filePathEdit = new QLineEdit(this);
    m_filePathEdit->setPlaceholderText(tr("C:\\path\\to\\sound.mp3"));
    m_browseButton = new QPushButton(tr("Browse"));
    fileLayout->addWidget(fileLabel);
    fileLayout->addWidget(m_filePathEdit);
    fileLayout->addWidget(m_browseButton);
    mainLayout->addLayout(fileLayout);

    // OK and Cancel buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton(tr("OK"));
    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
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
            tr("Select Sound File"),
            "",
            tr("Audio Files (*.mp3 *.wav *.WAV *.avi *.bwf *.ogg *.aif *.aiff *.caf)")
    );
    m_filePathEdit->setText(m_filePath);
}

QString AddButtonDialog::getName() const {
    return m_nameEdit->text();
}

QString AddButtonDialog::getFilePath() const {
    return m_filePath;
}

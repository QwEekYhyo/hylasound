#include <aboutdialog.hpp>

#include <QVBoxLayout>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("About HylaSound"));
    setFixedSize(320, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* logoLabel = new QLabel;
    logoLabel->setPixmap(QPixmap(":/hylasound.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(logoLabel);

    QLabel* nameLabel = new QLabel("HylaSound v1.0");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(nameLabel);

    QLabel* descLabel = new QLabel(tr("A simple soundboard application"));
    descLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(descLabel);

    QLabel* websiteLabel = new QLabel;
    websiteLabel->setText(tr("You can contribute to the source code <a href=\"https://github.com/QwEekYhyo/hylasound/\">here</a>"));
    websiteLabel->setTextFormat(Qt::RichText);
    websiteLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    websiteLabel->setOpenExternalLinks(true);
    websiteLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(websiteLabel);

    QLabel* copyrightLabel = new QLabel("Copyright © 2024 Logan Lucas");
    copyrightLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(copyrightLabel);

    m_createdByLabel = new QLabel(tr("Created by:<br><span style='color: #FF0000;'>Logan</span>"));
    m_createdByLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_createdByLabel);

    layout->addSpacing(20);

    QPushButton* okButton = new QPushButton(tr("OK"), this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okButton, 0, Qt::AlignCenter);

    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &AboutDialog::updateAnimation);
    m_animationTimer->start(500);
}

void AboutDialog::updateAnimation() {
    static QStringList colors = {"#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#FF00FF", "#00FFFF"};
    static int colorIndex = 0;

    colorIndex = (colorIndex + 1) % colors.size();
    m_createdByLabel->setText(QString(tr("Created by:<br><span style='color: %1;'>Logan</span>")).arg(colors[colorIndex]));
}

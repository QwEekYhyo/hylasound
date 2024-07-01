#include <buttongrid.hpp>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

ButtonGrid::ButtonGrid(QMediaPlayer* player, QWidget* parent) : QWidget(parent) {
    m_player = player;
    m_layout = new QGridLayout(this);
    m_buttons.reserve(50);
}

void ButtonGrid::addButton(const QString& name, const QString& filepath) {
    SoundButton* button = new SoundButton(name, filepath, m_player, this);
    m_buttons.append(button);

    int row = (m_buttons.size() - 1) / 10;
    int column = (m_buttons.size() - 1) % 10;

    m_layout->addWidget(button, row, column);
    connect(button, &SoundButton::removeRequested, this, &ButtonGrid::removeButton);

    saveButtonsToJson();
}

void ButtonGrid::removeButton(SoundButton* button) {
    int index = m_buttons.indexOf(button);
    if (index != -1) {
        m_buttons.removeAt(index);
        m_layout->removeWidget(button);
        button->deleteLater();

        // Rearrange remaining buttons
        for (int i = 0; i < m_buttons.size(); ++i) {
            int row = i / 10;
            int col = i % 10;
            m_layout->addWidget(m_buttons[i], row, col);
        }

        saveButtonsToJson();
    }
}

void ButtonGrid::saveButtonsToJson() {
    QJsonArray jsonArray;

    for (int i = 0; i < m_buttons.size(); i++) {
        QJsonObject buttonObject;

        buttonObject["id"] = i;
        buttonObject["name"] = m_buttons[i]->text();
        buttonObject["soundPath"] = m_buttons[i]->getSoundPath();
        jsonArray.append(buttonObject);
    }

    writeJsonFile(jsonArray);
}

void ButtonGrid::writeJsonFile(const QJsonArray& jsonArray) {
    QFile saveFile("test.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument buttonsDocument(jsonArray);
    saveFile.write(buttonsDocument.toJson());
}


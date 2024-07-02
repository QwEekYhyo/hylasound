#include <buttongrid.hpp>
#include <filenotfounddialog.hpp>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

const QString ButtonGrid::JSON_SAVE_FILE = "save.json";
const size_t ButtonGrid::MAX_COLUMN = 7;

ButtonGrid::ButtonGrid(QMediaPlayer* player, QWidget* parent) : QWidget(parent) {
    m_player = player;
    m_layout = new QGridLayout(this);
    m_buttons.reserve(50);

    loadButtonsFromJson();
}

void ButtonGrid::addButton(const QString& name, const QString& filepath) {
    SoundButton* button = new SoundButton(name, filepath, m_player, this);
    m_buttons.append(button);

    size_t row = (m_buttons.size() - 1) / ButtonGrid::MAX_COLUMN;
    size_t column = (m_buttons.size() - 1) % ButtonGrid::MAX_COLUMN;

    m_layout->addWidget(button, row, column);
    connect(button, &SoundButton::removeRequested, this, &ButtonGrid::removeButton);
    connect(button, &SoundButton::fileNotFound, this, &ButtonGrid::onFileNotFound);

    saveButtonsToJson();
}

void ButtonGrid::removeButton(SoundButton* button) {
    int index = m_buttons.indexOf(button);
    if (index != -1) {
        m_buttons.removeAt(index);
        m_layout->removeWidget(button);
        button->deleteLater();

        // Rearrange remaining buttons
        for (size_t i = 0; i < m_buttons.size(); i++) {
            size_t row = i / ButtonGrid::MAX_COLUMN;
            size_t col = i % ButtonGrid::MAX_COLUMN;
            m_layout->addWidget(m_buttons[i], row, col);
        }

        saveButtonsToJson();
    }
}

void ButtonGrid::clearAllButtons() {
    if (!m_buttons.isEmpty()) {
        while (!m_buttons.isEmpty()) {
            SoundButton* button = m_buttons.takeLast();
            m_layout->removeWidget(button);
            button->deleteLater();
        }

        saveButtonsToJson();
    }
}

void ButtonGrid::onFileNotFound(SoundButton* button) {
    FileNotFoundDialog dialog(button->getSoundPath(), this);
    dialog.exec();

    switch (dialog.getResult()) {
        case FileNotFoundDialog::Result::Dismiss:
            break;

        case FileNotFoundDialog::Result::Delete:
            removeButton(button);
            break;

        case FileNotFoundDialog::Result::Browse: {
                QString newFilePath = dialog.getNewFilePath();
                if (!newFilePath.isEmpty()) {
                    button->setSoundPath(newFilePath);
                    saveButtonsToJson();
                }
            }
            break;
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
    QFile saveFile(ButtonGrid::JSON_SAVE_FILE);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument buttonsDocument(jsonArray);
    saveFile.write(buttonsDocument.toJson());
}

void ButtonGrid::loadButtonsFromJson() {
    QJsonArray jsonArray = readJsonFile();

    for (size_t i = 0; i < jsonArray.size(); i++) {
        QJsonObject buttonObject = jsonArray[i].toObject();
        addButton(buttonObject["name"].toString(), buttonObject["soundPath"].toString());
    }
}

QJsonArray ButtonGrid::readJsonFile() {
    QFile loadFile(ButtonGrid::JSON_SAVE_FILE);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return QJsonArray();
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return loadDoc.array();
}

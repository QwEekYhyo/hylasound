#include <buttongrid.hpp>
#include <filenotfounddialog.hpp>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

const QString ButtonGrid::JSON_SAVE_FILE = "save.json";
const size_t ButtonGrid::MAX_COLUMN = 7;

ButtonGrid::ButtonGrid(QMediaPlayer* player, QWidget* parent) : QWidget(parent) {
    m_layout = new QGridLayout(this);
    m_layout->setHorizontalSpacing(10);
    m_layout->setVerticalSpacing(20);
    m_buttons.reserve(50);

    for (size_t i = 0; i < 4 * ButtonGrid::MAX_COLUMN; i++) {
        SoundButton* placeholderButton = new SoundButton(player, this);
        placeholderButton->setDisabled(true);
        m_buttons.append(placeholderButton);

        size_t row = i / ButtonGrid::MAX_COLUMN;
        size_t column = i % ButtonGrid::MAX_COLUMN;
        m_layout->addWidget(placeholderButton, row, column);
    }

    loadButtonsFromJson();
}

bool ButtonGrid::addButton(const QString& name, const QString& filepath) {
    if (m_cursor < m_buttons.size()) {
        SoundButton* button = m_buttons.at(m_cursor);
        button->setDisplayName(name);
        button->setSoundPath(filepath);
        button->setDisabled(false);

        connect(button, &SoundButton::removeRequested, this, &ButtonGrid::removeButton);
        connect(button, &SoundButton::fileNotFound, this, &ButtonGrid::onFileNotFound);

        m_cursor++;
        saveButtonsToJson();
        return true;
    }
    return false;
}

void ButtonGrid::removeButton(SoundButton* button) {
    int index = m_buttons.indexOf(button);
    if (index != -1) {
        button->setDisplayName("");
        button->setDisabled(true);
        // Rearrange item in the list
        for (size_t i = index; i < m_cursor && i < m_buttons.size() - 1; i++) {
            m_buttons.move(i + 1, i);
        }

        // Rearrange remaining buttons
        for (size_t i = index; i <= m_cursor && i < m_buttons.size(); i++) {
            size_t row = i / ButtonGrid::MAX_COLUMN;
            size_t col = i % ButtonGrid::MAX_COLUMN;
            m_layout->addWidget(m_buttons[i], row, col);
        }

        m_cursor--;
        saveButtonsToJson();
    }
}

void ButtonGrid::clearAllButtons() {
    if (m_cursor != 0) {
        while (m_cursor != 0) {
            SoundButton* button = m_buttons[m_cursor - 1];
            // need to call this method without saving to JSON
            removeButton(button);
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

    for (int i = 0; i < m_cursor; i++) {
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
        // need to call this method without saving to JSON
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

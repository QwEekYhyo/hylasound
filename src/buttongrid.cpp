#include <buttongrid.hpp>
#include <filenotfounddialog.hpp>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStyleOption>
#include <QPainter>

const size_t ButtonGrid::MAX_COLUMN = 7;

ButtonGrid::ButtonGrid(QMediaPlayer* player, QString jsonSaveFilePath, QWidget* parent) : QWidget(parent) {
    m_saveFilePath = jsonSaveFilePath;

    m_layout = new QGridLayout(this);
    m_layout->setHorizontalSpacing(10);
    m_layout->setVerticalSpacing(20);
    size_t numberOfButtons = 4 * ButtonGrid::MAX_COLUMN;
    m_buttons.reserve(numberOfButtons + 2);

    for (size_t i = 0; i < numberOfButtons; i++) {
        SoundButton* placeholderButton = new SoundButton(player, this);
        placeholderButton->setDisabled(true);
        m_buttons.append(placeholderButton);

        size_t row = i / ButtonGrid::MAX_COLUMN;
        size_t column = i % ButtonGrid::MAX_COLUMN;
        m_layout->addWidget(placeholderButton, row, column);
    }

    loadButtonsFromJson();
}

bool ButtonGrid::addButton(const QString& name, const QString& filepath, bool doSave) {
    if (m_cursor < m_buttons.size()) {
        SoundButton* button = m_buttons.at(m_cursor);
        button->setDisplayName(name);
        button->setSoundPath(filepath);
        button->setEnabled(true);
        button->style()->polish(button); // update style of added button

        connect(button, &SoundButton::removeRequested, this, &ButtonGrid::removeButton);
        connect(button, &SoundButton::fileNotFound, this, &ButtonGrid::onFileNotFound);

        m_cursor++;
        if (doSave)
            saveButtonsToJson();
        return true;
    }
    return false;
}

void ButtonGrid::removeButton(SoundButton* button, bool doSave) {
    int index = m_buttons.indexOf(button);
    if (index != -1) {
        button->setDisplayName("");
        button->setDisabled(true);
        button->style()->polish(button); // update style of "removed" button
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
        if (doSave)
            saveButtonsToJson();
    }
}

void ButtonGrid::clearAllButtons() {
    if (m_cursor != 0) {
        while (m_cursor != 0) {
            SoundButton* button = m_buttons[m_cursor - 1];
            removeButton(button, false);
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
    QFile saveFile(m_saveFilePath);
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
        addButton(buttonObject["name"].toString(), buttonObject["soundPath"].toString(), false);
    }
}

QJsonArray ButtonGrid::readJsonFile() {
    QFile loadFile(m_saveFilePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return QJsonArray();
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    return loadDoc.array();
}

void ButtonGrid::paintEvent(QPaintEvent* event) {
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

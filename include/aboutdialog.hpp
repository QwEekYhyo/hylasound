#pragma once

#include <QDialog>
#include <QLabel>
#include <QTimer>

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    AboutDialog(QWidget* parent = nullptr);

private slots:
    void updateAnimation();

private:
    QLabel* m_createdByLabel;
    QTimer* m_animationTimer;

};

#include "GameSettingDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

GameSettingDialog::GameSettingDialog(QWidget *parent) : QDialog(parent) {
    sizeBox = new QComboBox(this);
    for (int i = 6; i <= 12; i += 2)
        sizeBox->addItem(QString::number(i));

    obstacleBox = new QSpinBox(this);
    obstacleBox->setRange(0, 16);

    firstPlayerBox = new QComboBox(this);
    firstPlayerBox->addItems({"Black", "White", "Random"});

    okButton = new QPushButton("Confirm", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Board Size:"));
    layout->addWidget(sizeBox);
    layout->addWidget(new QLabel("Obstacle quantity:"));
    layout->addWidget(obstacleBox);
    layout->addWidget(new QLabel("First move:"));
    layout->addWidget(firstPlayerBox);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(okButton);
    btnLayout->addWidget(cancelButton);
    layout->addLayout(btnLayout);

    connect(okButton, &QPushButton::clicked, this, &GameSettingDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &GameSettingDialog::reject);
}

GameSettingDialog::GameConfig GameSettingDialog::getConfig() const {
    return { sizeBox->currentText().toInt(), obstacleBox->value(), firstPlayerBox->currentText() };
}

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
    firstPlayerBox->addItems({"흑", "백", "무작위"});

    okButton = new QPushButton("확인", this);
    cancelButton = new QPushButton("취소", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("보드 크기:"));
    layout->addWidget(sizeBox);
    layout->addWidget(new QLabel("장애물 개수:"));
    layout->addWidget(obstacleBox);
    layout->addWidget(new QLabel("선공 플레이어:"));
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

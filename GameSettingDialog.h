#ifndef GAMESETTINGDIALOG_H
#define GAMESETTINGDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

class GameSettingDialog : public QDialog {
    Q_OBJECT
public:
    struct GameConfig {
        int boardSize;
        int obstacleCount;
        QString firstPlayer;
    };

    GameSettingDialog(QWidget *parent = nullptr);
    GameConfig getConfig() const;

private:
    QComboBox *sizeBox;
    QSpinBox *obstacleBox;
    QComboBox *firstPlayerBox;
    QPushButton *okButton, *cancelButton;
};

#endif

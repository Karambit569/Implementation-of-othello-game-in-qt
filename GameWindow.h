#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "GameBoardWidget.h"

class GameWindow : public QWidget {
    Q_OBJECT
public:
    explicit GameWindow(const GameSettingDialog::GameConfig &config, QWidget *parent = nullptr);

private:
    GameBoardWidget *boardWidget;
    QLabel *turnLabel;
    QLabel *blackCountLabel;
    QLabel *whiteCountLabel;
    QPushButton *backButton;

private slots:
    void goToMainMenu();
};

#endif // GAMEWINDOW_H

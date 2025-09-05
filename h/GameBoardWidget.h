#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QWidget>
#include <QVector>
#include <QSet>
#include <QPair>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "GameSettingDialog.h"
#include "GameState.h"

class GameBoardWidget : public QWidget {
    Q_OBJECT
public:
    
    explicit GameBoardWidget(const GameSettingDialog::GameConfig &config, QWidget *parent = nullptr);

   
    explicit GameBoardWidget(const GameState &state, QWidget *parent = nullptr);

    GameState getCurrentState() const { return currentState; }

signals:
    void requestReturnToMain(GameState latestState); 

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUI();
    void updateStatusLabels();
    void calculateValidMoves();
    void flipStones(int row, int col);

    GameState currentState;
    QSet<QPair<int, int>> validMoves;

    // UI
    QLabel *turnLabel;
    QLabel *turnCountLabel;
    QLabel *scoreLabel;
    QPushButton *saveAndReturnBtn;
    QVBoxLayout *rightPanelLayout;
    QWidget *rightPanel;
};

#endif // GAMEBOARDWIDGET_H

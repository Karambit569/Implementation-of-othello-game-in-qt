#ifndef REPLAYWINDOW_H
#define REPLAYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include "GameState.h"
#include "GameBoardWidget.h"

class ReplayWindow : public QWidget {
    Q_OBJECT
public:
    explicit ReplayWindow(const QList<GameState> &history, QWidget *parent = nullptr);

private slots:
    void prevTurn();
    void nextTurn();

private:
    QList<GameState> history;
    int currentIndex;

    QPushButton *prevBtn;
    QPushButton *nextBtn;
    QSlider *slider;

    GameBoardWidget *boardView;
};

#endif

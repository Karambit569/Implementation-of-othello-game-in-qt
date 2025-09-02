#include "ReplayWindow.h"
#include <QVBoxLayout>

ReplayWindow::ReplayWindow(const QList<GameState> &history, QWidget *parent)
    : QWidget(parent), history(history), currentIndex(0) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    boardView = new GameBoardWidget(history[0], this);
    boardView->setMinimumSize(400, 400);

    prevBtn = new QPushButton("이전", this);
    nextBtn = new QPushButton("다음", this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, history.size() - 1);

    layout->addWidget(boardView);
    layout->addWidget(prevBtn);
    layout->addWidget(nextBtn);
    layout->addWidget(slider);

    connect(prevBtn, &QPushButton::clicked, this, &ReplayWindow::prevTurn);
    connect(nextBtn, &QPushButton::clicked, this, &ReplayWindow::nextTurn);
    connect(slider, &QSlider::valueChanged, [=](int value) {
        currentIndex = value;
        boardView->deleteLater();
        boardView = new GameBoardWidget(history[currentIndex], this);
        boardView->setMinimumSize(400, 400);
        layout->insertWidget(0, boardView);
    });
}

void ReplayWindow::prevTurn() {
    if (currentIndex > 0) slider->setValue(--currentIndex);
}

void ReplayWindow::nextTurn() {
    if (currentIndex < history.size() - 1) slider->setValue(++currentIndex);
}

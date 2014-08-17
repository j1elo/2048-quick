#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

class Board;

class GameManager : public QObject
{
    Q_OBJECT

public:
    GameManager(QObject* parent = 0);

    void startNewGame();

public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

signals:
    void tileAdded(int index, int value);
    void tileMoved(int fromIndex, int toIndex);
    void tilesMerged(int fromIndex, int toIndex, int value);

private:
    Board* m_board;
};

#endif // GAMEMANAGER_H

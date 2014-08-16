#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

class BoardItem;

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
    void valueAdded(int index, int value);
    void valueMoved(int fromIndex, int toIndex);
    void valueChanged(int index, int value);

private:
    BoardItem* m_boardItem;
};

#endif // GAMEMANAGER_H

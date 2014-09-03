#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QString>
#include <QVector>
#include <functional>

class Board : public QObject
{
    Q_OBJECT

    friend class BoardTest;
    typedef std::function<int (int, int)> IndexFn;

public:
    Board(int numRows, int numCols);

    void addRandomTile();

    bool isFull();
    QString toString();

    // Make tiles fall towards a specific direction
    // Returns true if it generates any movement
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

signals:
    void tileAdded(int index, int value);
    void tileMoved(int fromIndex, int toIndex, int newValue = 0);

private:
    int cell(int row, int col);

    // Calculate the new data matrix after letting all its values
    // "fall" towards the direction defined by the index() function parameter.
    bool fall(int majorSize, int minorSize, IndexFn index);

private:
    int m_numRows;
    int m_numCols;
    QVector<int> m_data;
};

#endif // BOARD_H

#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QObject>
#include <QString>
#include <QVector>
#include <functional>

class BoardItem : public QObject
{
    Q_OBJECT

    friend class BoardItemTest;
    typedef std::function<int (int, int)> IndexFn;

public:
    BoardItem(int numRows, int numCols);

//    void setCell(int row, int col, int value);
    void setCellRandom();

    bool isFull();
    QString toString();

    // Return true if it generates any movement
    bool fallUp();
    bool fallDown();
    bool fallLeft();
    bool fallRight();

signals:
    void valueAdded(int index, int value);
    void valueMoved(int fromIndex, int toIndex);
    void valueChanged(int index, int value);

private:
    int cell(int row, int col);
    bool fall(int majorSize, int minorSize, IndexFn index);

private:
    int m_numRows;
    int m_numCols;
    QVector<int> m_data;
};

#endif // BOARDITEM_H

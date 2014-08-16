#include "BoardItem.h"

#include <QtDebug>
#include <QtMath> // qrand, qFloor, log10
#include <QTime>

BoardItem::BoardItem(int numRows, int numCols)
    : m_numRows(numRows)
    , m_numCols(numCols)
{
    m_data.fill(0, numRows * numCols);
    qsrand(QTime::currentTime().msec());
}

int BoardItem::cell(int row, int col)
{
    Q_ASSERT(row * m_numCols + col < m_data.size());
    return m_data[row * m_numCols + col];
}

//void BoardItem::setCell(int row, int col, int value)
//{
//    Q_ASSERT(row * m_numCols + col < m_data.size());
//    m_data[row * m_numCols + col] = value;
//    emit cellSet(row, col, value);
//}

void BoardItem::setCellRandom()
{
    // First find an empty space
    if (isFull()) {
        return;
    }
    int index;
    do {
        index = qrand() % m_data.size();
    } while (m_data[index] != 0);

    // Now, insert there
//    int row = qFloor((double)index / m_numCols);
//    int col = index % m_numCols;
//    int value = ((double)qrand() / RAND_MAX) < 0.9 ? 2 : 4;
//    setCell(row, col, value);
    int value = ((double)qrand() / RAND_MAX) < 0.9 ? 2 : 4;
    m_data[index] = value;
    emit valueAdded(index, value);
}

bool BoardItem::isFull()
{
    return m_data.indexOf(0, 0) == -1;
}

QString BoardItem::toString()
{
    // Find biggest field width for the matrix
    int biggest = 1; // N > 0 for a safe log10(N)
    foreach(int value, m_data) {
        if (value > biggest) {
            biggest = value;
        }
    }
    int fieldWidth = qFloor(log10((double)biggest)) + 1;

    // Now generate the string
    QString str = "";
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numCols; j++) {
            str += QString("[%1]").arg(cell(i, j), fieldWidth);
        }
        str += "\n";
    }
    return str;
}

bool BoardItem::fallUp()
{
    return fall(
        // Access in column-major order
        m_numCols, m_numRows,
        [this](int col, int row){ return row * m_numCols + col; }
    );
}

bool BoardItem::fallDown()
{
    return fall(
        // Access in inverse column-major order
        m_numCols, m_numRows,
        [this](int col, int row){ return (m_numRows * m_numCols - 1) - (row * m_numCols + col); }
    );
}

bool BoardItem::fallLeft()
{
    return fall(
        // Access in row-major order
        m_numRows, m_numCols,
        [this](int row, int col){ return row * m_numCols + col; }
    );
}

bool BoardItem::fallRight()
{
    return fall(
        // Access in inverse row-major order
        m_numRows, m_numCols,
        [this](int row, int col){ return row * m_numCols + m_numCols - 1 - col; }
    );
}

bool BoardItem::fall(int majorSize, int minorSize, IndexFn index)
{
    bool moved = false;

    for (int major = 0; major < majorSize; major++) {
        int fall = 0; // Index of the next place where to fall or merge
        int minor = 1; // Iterates over all the values in current major dimension
        while (minor < minorSize) {
            while (minor < minorSize && m_data[index(major, minor)] == 0) {
                minor++;
            }
            if (minor >= minorSize) {
                continue;
            }
            if (m_data[index(major, fall)] == m_data[index(major, minor)]) {
                // Merge
                m_data[index(major, fall)] = m_data[index(major, fall)] + m_data[index(major, minor)];
                m_data[index(major, minor)] = 0;
                moved = true;
                emit valueMoved(index(major, minor), index(major, fall));
                emit valueChanged(index(major, fall), m_data[index(major, fall)]);
                fall++;
            }
            else if (m_data[index(major, fall)] == 0) {
                // Fall
                m_data[index(major, fall)] = m_data[index(major, minor)];
                m_data[index(major, minor)] = 0;
                moved = true;
                emit valueMoved(index(major, minor), index(major, fall));
            }
            else {
                // Neither merge nor fall
                fall++;

                if (fall != minor) {
                    // Fall
                    m_data[index(major, fall)] = m_data[index(major, minor)];
                    m_data[index(major, minor)] = 0;
                    moved = true;
                    emit valueMoved(index(major, minor), index(major, fall));
                }
            }
            minor++;
        }
    }

    return moved;
}

#include "Board.h"

#include <QtDebug>
#include <QtMath> // qrand, qFloor, <math.h>
#include <QTime>
#include <algorithm> // std::max_element

Board::Board(int numRows, int numCols)
    : m_numRows(numRows)
    , m_numCols(numCols)
{
    m_data.fill(0, numRows * numCols);
    qsrand(QTime::currentTime().msec());
}

int Board::cell(int row, int col)
{
    Q_ASSERT(row * m_numCols + col < m_data.size());
    return m_data[row * m_numCols + col];
}

//void Board::setCell(int row, int col, int value)
//{
//    Q_ASSERT(row * m_numCols + col < m_data.size());
//    m_data[row * m_numCols + col] = value;
//    emit cellSet(row, col, value);
//}

void Board::addRandomTile()
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
    emit tileAdded(index, value);
}

bool Board::isFull()
{
    return m_data.indexOf(0, 0) == -1;
}

QString Board::toString()
{
    // Determine what's the longest field width
    // needed for representing the whole matrix
    int max = *std::max_element(m_data.begin(), m_data.end());
    if (max < 1) max = 1; // log10(N) requires N > 0
    int fieldWidth = qFloor(log10(max)) + 1;

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

bool Board::moveUp()
{
    return fall(
        // Access in column-major order
        m_numCols, m_numRows,
        [this](int col, int row){ return row * m_numCols + col; }
    );
}

bool Board::moveDown()
{
    return fall(
        // Access in inverse column-major order
        m_numCols, m_numRows,
        [this](int col, int row){ return (m_numRows * m_numCols - 1) - (row * m_numCols + col); }
    );
}

bool Board::moveLeft()
{
    return fall(
        // Access in row-major order
        m_numRows, m_numCols,
        [this](int row, int col){ return row * m_numCols + col; }
    );
}

bool Board::moveRight()
{
    return fall(
        // Access in inverse row-major order
        m_numRows, m_numCols,
        [this](int row, int col){ return row * m_numCols + m_numCols - 1 - col; }
    );
}

bool Board::fall(int majorSize, int minorSize, IndexFn index)
{
    /*
     * This algorithm modifies the current data matrix to simulate
     * how all its elements would fall towards a given direction, combining
     * themselves when appropriate or othewise just piling up one over each other.
     *
     * The easiest way of reasoning about the implementation is thinking on the
     * basic case of FallLeft: all elements fall towards the left side.
     * The matrix is traversed from left to right and from top to bottom,
     * calculating new number positions and values.
     *
     * This base case is then generalized by means of the index() function, which
     * transparently translates all accesses to the data matrix in order to
     * allow the same algorithm work independently of the actual direction
     * of the fall.
     */

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
                emit tilesMerged(index(major, minor), index(major, fall), m_data[index(major, fall)]);
                fall++;
            }
            else if (m_data[index(major, fall)] == 0) {
                // Fall
                m_data[index(major, fall)] = m_data[index(major, minor)];
                m_data[index(major, minor)] = 0;
                moved = true;
                emit tileMoved(index(major, minor), index(major, fall));
            }
            else {
                // Neither merge nor fall
                fall++;

                if (fall != minor) {
                    // Fall
                    m_data[index(major, fall)] = m_data[index(major, minor)];
                    m_data[index(major, minor)] = 0;
                    moved = true;
                    emit tileMoved(index(major, minor), index(major, fall));
                }
            }
            minor++;
        }
    }

    return moved;
}

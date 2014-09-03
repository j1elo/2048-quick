#include "GameManager.h"
#include "Board.h"

#include <QtDebug>

GameManager::GameManager(QObject* parent)
    : QObject(parent)
    , m_board(nullptr)
{}

void GameManager::startNewGame()
{
    delete m_board;
    m_board = new Board(4, 4);

    connect(m_board, SIGNAL(tileAdded(int,int)), this, SIGNAL(tileAdded(int,int)));
    connect(m_board, SIGNAL(tileMoved(int,int,int)), this, SIGNAL(tileMoved(int,int,int)));

    m_board->addRandomTile();
    qDebug() << qPrintable(m_board->toString());
}

void GameManager::moveUp()
{
    Q_ASSERT(m_board);
    if (m_board->moveUp()) {
        m_board->addRandomTile();
    }
    qDebug() << qPrintable(m_board->toString());
}

void GameManager::moveDown()
{
    Q_ASSERT(m_board);
    if (m_board->moveDown()) {
        m_board->addRandomTile();
    }
    qDebug() << qPrintable(m_board->toString());
}

void GameManager::moveLeft()
{
    Q_ASSERT(m_board);
    if (m_board->moveLeft()) {
        m_board->addRandomTile();
    }
    qDebug() << qPrintable(m_board->toString());
}

void GameManager::moveRight()
{
    Q_ASSERT(m_board);
    if (m_board->moveRight()) {
        m_board->addRandomTile();
    }
    qDebug() << qPrintable(m_board->toString());
}

#include "GameManager.h"
#include "BoardItem.h"

#include <QtDebug>

GameManager::GameManager(QObject* parent)
    : QObject(parent)
    , m_boardItem(nullptr)
{}

void GameManager::startNewGame()
{
    delete m_boardItem;
    m_boardItem = new BoardItem(4, 4);

    connect(m_boardItem, SIGNAL(valueAdded(int,int)), this, SIGNAL(valueAdded(int,int)));
    connect(m_boardItem, SIGNAL(valueMoved(int,int)), this, SIGNAL(valueMoved(int,int)));
    connect(m_boardItem, SIGNAL(valueChanged(int,int)), this, SIGNAL(valueChanged(int,int)));

    m_boardItem->setCellRandom();
    qDebug() << qPrintable(m_boardItem->toString());
}

void GameManager::moveUp()
{
    Q_ASSERT(m_boardItem);
    if (m_boardItem->fallUp()) {
        m_boardItem->setCellRandom();
    }
    qDebug() << qPrintable(m_boardItem->toString());
}

void GameManager::moveDown()
{
    Q_ASSERT(m_boardItem);
    if (m_boardItem->fallDown()) {
        m_boardItem->setCellRandom();
    }
    qDebug() << qPrintable(m_boardItem->toString());
}

void GameManager::moveLeft()
{
    Q_ASSERT(m_boardItem);
    if (m_boardItem->fallLeft()) {
        m_boardItem->setCellRandom();
    }
    qDebug() << qPrintable(m_boardItem->toString());
}

void GameManager::moveRight()
{
    Q_ASSERT(m_boardItem);
    if (m_boardItem->fallRight()) {
        m_boardItem->setCellRandom();
    }
    qDebug() << qPrintable(m_boardItem->toString());
}

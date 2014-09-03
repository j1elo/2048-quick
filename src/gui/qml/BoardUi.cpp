#include "BoardUi.h"
#include "core/GameManager.h"

#include <QtDebug>
#include <QVariant>

BoardUi::BoardUi(QObject* parent)
    : BaseUi(parent)
{
    setObjectName(metaObject()->className());
}

void BoardUi::setGameManager(GameManager* game)
{
    qDebug() << "[BoardUi::setGameManager]" << "objectName:" << objectName();
    this->disconnect();
    if (game) {
        connect(game, SIGNAL(tileAdded(int,int)), this, SLOT(addTile(int,int)));
        connect(game, SIGNAL(tileMoved(int,int,int)), this, SLOT(moveTile(int,int,int)));

        Q_ASSERT(m_root);
        connect(m_root, SIGNAL(upPressed()), game, SLOT(moveUp()));
        connect(m_root, SIGNAL(downPressed()), game, SLOT(moveDown()));
        connect(m_root, SIGNAL(leftPressed()), game, SLOT(moveLeft()));
        connect(m_root, SIGNAL(rightPressed()), game, SLOT(moveRight()));
    }
}

void BoardUi::rootSetup()
{
    qDebug() << "[BoardUi::rootSetup]" << "objectName:" << objectName();
}

void BoardUi::addTile(int index, int value)
{
    Q_ASSERT(m_root);
    QMetaObject::invokeMethod(m_root, "addTile",
        Q_ARG(QVariant, index), Q_ARG(QVariant, value));
}

void BoardUi::moveTile(int fromIndex, int toIndex, int newValue)
{
    Q_ASSERT(m_root);
    QMetaObject::invokeMethod(m_root, "moveTile",
        Q_ARG(QVariant, fromIndex), Q_ARG(QVariant, toIndex), Q_ARG(QVariant, newValue));
}

#include "MainWindowUi.h"
#include "BoardUi.h"
#include "core/GameManager.h"

#include <QtDebug>
#include <QVariant>
#include <QTimer>

MainWindowUi::MainWindowUi(QObject* parent)
    : BaseUi(parent)
    , m_boardUi(new BoardUi(this))
{
    setObjectName(metaObject()->className());
}

void MainWindowUi::rootSetup()
{
    qDebug() << "[MainWindowUi::rootSetup]" << "objectName:" << objectName();
    Q_ASSERT(m_root);

    QObject* childQML = m_root->findChild<QObject*>("BoardQML");
    Q_ASSERT(childQML);
    m_boardUi->setRootObject(childQML);

    // TODO: this will be triggered by an action from the main menu
    QTimer::singleShot(1000, this, SLOT(onNewGameRequested()));
}

void MainWindowUi::onNewGameRequested()
{
    GameManager* gameManager = new GameManager(this);
    m_boardUi->setGameManager(gameManager);
    gameManager->startNewGame();
}

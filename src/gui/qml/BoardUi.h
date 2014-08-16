#ifndef BOARDUI_H
#define BOARDUI_H

#include "BaseUi.h"

class GameManager;

class BoardUi : public BaseUi
{
    Q_OBJECT

public:
    BoardUi(QObject* parent = 0);

    void setGameManager(GameManager* game);

protected:
    virtual void rootSetup();

private slots:
    // React to changes in data model
    void addTile(int index, int value);
    void moveTile(int fromIndex, int toIndex);
    void setTile(int index, int value);
};

#endif // BOARDUI_H

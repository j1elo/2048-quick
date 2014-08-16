#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#include "BaseUi.h"

class BoardUi;

class MainWindowUi : public BaseUi
{
    Q_OBJECT

public:
    MainWindowUi(QObject* parent = 0);
//    virtual ~MainWindowUi();

protected:
    virtual void rootSetup();

private slots:
    void onNewGameRequested();

private:
    BoardUi* m_boardUi;
};

#endif // MAINWINDOWUI_H

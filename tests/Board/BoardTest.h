#ifndef BOARDTEST_H
#define BOARDTEST_H

#include <QtTest/QTest>

class BoardTest : public QObject
{
    Q_OBJECT

private slots:
    void fallUpLeft();
    void fallUpLeft_data();

    void fallDownRight();
    void fallDownRight_data();
};

#endif // BOARDTEST_H

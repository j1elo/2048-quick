#include "BoardTest.h"
#include "Board.h"

#include <QtDebug>
#include <QVector>
#include <QString>

struct TestCase
{
    TestCase(QVector<int> inputV = QVector<int>(), QVector<int> resultV = QVector<int>())
        : input(inputV)
        , result(resultV)
    {
        tag = "[";
        foreach (int value, inputV) { tag += QString::number(value); }
        tag += "]";
    }

    QVector<int> input;
    QVector<int> result;
    QString tag;
};

void BoardTest::fallUpLeft()
{
    QFETCH(QVector<int>, input);
    QFETCH(QVector<int>, result);

    // Test falling up
    Board boardUp(input.size(), 1);
    boardUp.m_data = input;
    boardUp.fallUp();
    QCOMPARE(boardUp.m_data, result);

    // Test falling left
    Board boardLeft(1, input.size());
    boardLeft.m_data = input;
    boardLeft.fallLeft();
    QCOMPARE(boardLeft.m_data, result);
}

void BoardTest::fallUpLeft_data()
{
    QTest::addColumn< QVector<int> >("input");
    QTest::addColumn< QVector<int> >("result");

    QVector<TestCase> cases;
    cases
            << TestCase((QVector<int>()), (QVector<int>()))
            << TestCase((QVector<int>()<<0), (QVector<int>()<<0))
            << TestCase((QVector<int>()<<1), (QVector<int>()<<1))
            << TestCase((QVector<int>()<<0<<0), (QVector<int>()<<0<<0))
            << TestCase((QVector<int>()<<0<<1), (QVector<int>()<<1<<0))
            << TestCase((QVector<int>()<<1<<0), (QVector<int>()<<1<<0))
            << TestCase((QVector<int>()<<1<<1), (QVector<int>()<<2<<0))
            << TestCase((QVector<int>()<<1<<2), (QVector<int>()<<1<<2))
            << TestCase((QVector<int>()<<2<<1), (QVector<int>()<<2<<1))

            << TestCase((QVector<int>()<<0<<0<<0), (QVector<int>()<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<1), (QVector<int>()<<1<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<0), (QVector<int>()<<1<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<1), (QVector<int>()<<2<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<0), (QVector<int>()<<1<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<1), (QVector<int>()<<2<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<0), (QVector<int>()<<2<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<1), (QVector<int>()<<2<<1<<0))

            << TestCase((QVector<int>()<<1<<1<<1), (QVector<int>()<<2<<1<<0))
            << TestCase((QVector<int>()<<1<<1<<2), (QVector<int>()<<2<<2<<0))
            << TestCase((QVector<int>()<<1<<2<<1), (QVector<int>()<<1<<2<<1))
            << TestCase((QVector<int>()<<1<<2<<2), (QVector<int>()<<1<<4<<0))
            << TestCase((QVector<int>()<<2<<1<<1), (QVector<int>()<<2<<2<<0))
            << TestCase((QVector<int>()<<2<<1<<2), (QVector<int>()<<2<<1<<2))
            << TestCase((QVector<int>()<<2<<2<<1), (QVector<int>()<<4<<1<<0))
            << TestCase((QVector<int>()<<2<<2<<2), (QVector<int>()<<4<<2<<0))

            << TestCase((QVector<int>()<<0<<0<<0<<0), (QVector<int>()<<0<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<0<<1), (QVector<int>()<<1<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<1<<0), (QVector<int>()<<1<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<1<<1), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<0<<0), (QVector<int>()<<1<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<0<<1), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<1<<0), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<1<<1<<1), (QVector<int>()<<2<<1<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<0<<0), (QVector<int>()<<1<<0<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<0<<1), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<1<<0), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<1<<0<<1<<1), (QVector<int>()<<2<<1<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<0<<0), (QVector<int>()<<2<<0<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<0<<1), (QVector<int>()<<2<<1<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<1<<0), (QVector<int>()<<2<<1<<0<<0))
            << TestCase((QVector<int>()<<1<<1<<1<<1), (QVector<int>()<<2<<2<<0<<0));

    for (int i = 0; i < cases.size(); i++) {
        QTest::newRow(qPrintable(cases[i].tag)) << cases[i].input << cases[i].result;
    }
}

void BoardTest::fallDownRight()
{
    QFETCH(QVector<int>, input);
    QFETCH(QVector<int>, result);

    // Test falling down
    Board boardDown(input.size(), 1);
    boardDown.m_data = input;
    boardDown.fallDown();
    QCOMPARE(boardDown.m_data, result);

    // Test falling right
    Board boardRight(1, input.size());
    boardRight.m_data = input;
    boardRight.fallRight();
    QCOMPARE(boardRight.m_data, result);
}

void BoardTest::fallDownRight_data()
{
    QTest::addColumn< QVector<int> >("input");
    QTest::addColumn< QVector<int> >("result");

    QVector<TestCase> cases;
    cases
            << TestCase((QVector<int>()), (QVector<int>()))
            << TestCase((QVector<int>()<<0), (QVector<int>()<<0))
            << TestCase((QVector<int>()<<1), (QVector<int>()<<1))
            << TestCase((QVector<int>()<<0<<0), (QVector<int>()<<0<<0))
            << TestCase((QVector<int>()<<0<<1), (QVector<int>()<<0<<1))
            << TestCase((QVector<int>()<<1<<0), (QVector<int>()<<0<<1))
            << TestCase((QVector<int>()<<1<<1), (QVector<int>()<<0<<2))
            << TestCase((QVector<int>()<<1<<2), (QVector<int>()<<1<<2))
            << TestCase((QVector<int>()<<2<<1), (QVector<int>()<<2<<1))

            << TestCase((QVector<int>()<<0<<0<<0), (QVector<int>()<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<1), (QVector<int>()<<0<<0<<1))
            << TestCase((QVector<int>()<<0<<1<<0), (QVector<int>()<<0<<0<<1))
            << TestCase((QVector<int>()<<0<<1<<1), (QVector<int>()<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<0<<0), (QVector<int>()<<0<<0<<1))
            << TestCase((QVector<int>()<<1<<0<<1), (QVector<int>()<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<1<<0), (QVector<int>()<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<1<<1), (QVector<int>()<<0<<1<<2))

            << TestCase((QVector<int>()<<1<<1<<1), (QVector<int>()<<0<<1<<2))
            << TestCase((QVector<int>()<<1<<1<<2), (QVector<int>()<<0<<2<<2))
            << TestCase((QVector<int>()<<1<<2<<1), (QVector<int>()<<1<<2<<1))
            << TestCase((QVector<int>()<<1<<2<<2), (QVector<int>()<<0<<1<<4))
            << TestCase((QVector<int>()<<2<<1<<1), (QVector<int>()<<0<<2<<2))
            << TestCase((QVector<int>()<<2<<1<<2), (QVector<int>()<<2<<1<<2))
            << TestCase((QVector<int>()<<2<<2<<1), (QVector<int>()<<0<<4<<1))
            << TestCase((QVector<int>()<<2<<2<<2), (QVector<int>()<<0<<2<<4))

            << TestCase((QVector<int>()<<0<<0<<0<<0), (QVector<int>()<<0<<0<<0<<0))
            << TestCase((QVector<int>()<<0<<0<<0<<1), (QVector<int>()<<0<<0<<0<<1))
            << TestCase((QVector<int>()<<0<<0<<1<<0), (QVector<int>()<<0<<0<<0<<1))
            << TestCase((QVector<int>()<<0<<0<<1<<1), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<0<<1<<0<<0), (QVector<int>()<<0<<0<<0<<1))
            << TestCase((QVector<int>()<<0<<1<<0<<1), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<0<<1<<1<<0), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<0<<1<<1<<1), (QVector<int>()<<0<<0<<1<<2))
            << TestCase((QVector<int>()<<1<<0<<0<<0), (QVector<int>()<<0<<0<<0<<1))
            << TestCase((QVector<int>()<<1<<0<<0<<1), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<0<<1<<0), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<0<<1<<1), (QVector<int>()<<0<<0<<1<<2))
            << TestCase((QVector<int>()<<1<<1<<0<<0), (QVector<int>()<<0<<0<<0<<2))
            << TestCase((QVector<int>()<<1<<1<<0<<1), (QVector<int>()<<0<<0<<1<<2))
            << TestCase((QVector<int>()<<1<<1<<1<<0), (QVector<int>()<<0<<0<<1<<2))
            << TestCase((QVector<int>()<<1<<1<<1<<1), (QVector<int>()<<0<<0<<2<<2));

    for (int i = 0; i < cases.size(); i++) {
        QTest::newRow(qPrintable(cases[i].tag)) << cases[i].input << cases[i].result;
    }
}

QTEST_MAIN(BoardTest)

#ifndef BASEUI_H
#define BASEUI_H

#include <QtDebug>
#include <QObject>
#include <QVariant>

class BaseUi : public QObject
{
    Q_OBJECT

public:
    BaseUi(QObject* parent = 0)
        : QObject(parent)
        , m_root(nullptr)
    {
        setObjectName(metaObject()->className());
    }

    virtual ~BaseUi()
    {
        qDebug() << "[BaseUi::~BaseUi]" << "objectName:" << objectName();
    }

    virtual void setRootObject(QObject* root)
    {
        qDebug() << "[BaseUi::setRootObject]" << "objectName:" << objectName();
        if (m_root != root) {
            if (m_root) {
                disconnect(m_root); // Disconnect from any previous root
            }
            m_root = root;
            if (m_root) {
                rootSetup();
            }
        }
    }

protected:
    // In this method, derived classes should initialize their interaction
    // with their ui root object (eg. connect to signals).
    virtual void rootSetup() {
        qDebug() << "[BaseUi::rootSetup]" << "objectName:" << objectName() << "(do nothing)";
        Q_ASSERT(m_root);
    }

protected:
    QObject* m_root;
};

#endif // BASEUI_H

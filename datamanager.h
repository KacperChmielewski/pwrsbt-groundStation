#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include "logger.h"

class dataManager : public QObject
{
    Q_OBJECT
private:
    logger* log;
public:
    explicit dataManager(QObject *parent = nullptr);
    void setLogger(logger* l);

signals:

public slots:
};

#endif // DATAMANAGER_H

#include "datamanager.h"

dataManager::dataManager(QObject *parent) : QObject(parent)
{

}

void dataManager::setLogger(logger* l) {
    this->log = l;
    this->log->print("dataManager Init");
}

#ifndef guiworker_h
#define guiworker_h

#include "guiworker.h"
#include <QFile>

GUIWorker::GUIWorker()
{
}

void GUIWorker::doSomething()
{
        emit finished(true);
}

#endif


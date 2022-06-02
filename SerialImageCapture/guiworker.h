#ifndef GUIWORKER_H
#define GUIWORKER_H
#include <QObject>

class GUIWorker : public QObject
{
        Q_OBJECT

public:
        GUIWorker();

public slots:
        void doSomething();

signals:
        void finished(bool success);
};

#endif // GUIWORKER_H

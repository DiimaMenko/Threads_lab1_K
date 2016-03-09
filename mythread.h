#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>

class MyThread : public QThread
{
    int startPosition;
    int endPosition;
    QVector<QVector< int> > matrix;
public:
    MyThread();
    MyThread(int startPos, int endPos, QVector<QVector<int> > m);
    void run();
    QVector<QVector< int> > getMatrix();
};

#endif // MYTHREAD_H

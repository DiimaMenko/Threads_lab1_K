#include "mythread.h"
#include <QDebug>

MyThread::MyThread()
{

}

MyThread::MyThread(int startPos, int endPos, QVector<QVector<int> > m){
    this->startPosition = startPos;
    this->matrix = m;
    if(endPos < this->matrix.size())
        this->endPosition = endPos;
    else
        this->endPosition = m.size();
}

void MyThread::run(){
    for(int k = this->startPosition; k < this->endPosition; k++){
        for(int l = 0; l < this->matrix.size() / 2; l++){
            if(l < k){
                int t = this->matrix[k][l];
                this->matrix[k][l] = this->matrix[k][this->matrix.size() - 1 - l];
                this->matrix[k][this->matrix.size() - 1 - l] = t;
            }
        }
    }
}

QVector<QVector< int> > MyThread::getMatrix(){
    return this->matrix;
}

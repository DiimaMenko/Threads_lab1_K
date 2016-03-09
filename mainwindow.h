#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mythread.h>
#include <QVector>
#include <QString>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<QVector< int> > matrix;
    int numberOfElements;
    int numberOfThreads;
    QString textMatrix;
    QString textResultMatrix;

public slots:
    void start();
    QString makeTextFromMatrix();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

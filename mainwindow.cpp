#include "mainwindow.h"
#include "ui_mainwindow.h"

static QVector<MyThread*> myThreads;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(start()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(){
    myThreads.resize(0);
    this->numberOfElements = this->ui->lineEditNumberOfElements->text().toInt();
    if(this->numberOfElements > 3){
        this->matrix.resize(this->numberOfElements);
        for(int i = 0; i < this->numberOfElements; i++){
            this->matrix[i].resize(this->numberOfElements);
            for(int j = 0; j < this->numberOfElements; j++){
                this->matrix[i][j] = rand()%100;
            }
        }
        this->textMatrix = makeTextFromMatrix();
        this->ui->labelMatrix->setText(this->textMatrix);
    }
    this->numberOfThreads = this->ui->lineEditNumberOfThreads->text().toInt();
    int startPos = 0;
    int endPos = 0;
    if(this->numberOfThreads > 0 && this->numberOfElements > 3){        
        for(int i = 0; i < this->numberOfThreads; i++){
            startPos = endPos;
            endPos = this->numberOfElements / numberOfThreads * (i + 1);
            if(endPos > this->numberOfElements)
                endPos = this->numberOfElements;
            MyThread *temp = new MyThread(startPos, endPos, this->matrix);
            myThreads.push_back(temp);
        }
        int startTime = QTime::currentTime().msecsSinceStartOfDay();
        for(int i = 0; i < this->numberOfThreads; i++){
            myThreads[i]->start();
        }
        for(int i = 0; i < this->numberOfThreads; i++){
            myThreads[i]->wait();
        }
        int endTime = QTime::currentTime().msecsSinceStartOfDay();
        int resultTime = endTime - startTime;
        for(int k = 0; k < this->numberOfThreads; k++){
            for(int i = this->numberOfElements / numberOfThreads * k; i < this->matrix.size(); i++){
                for(int j = 0; j < this->matrix.size(); j++){
                    this->matrix[i][j] = myThreads[k]->getMatrix()[i][j];
                }
            }
        }

        this->ui->labelTime->setText(QString::number(resultTime));
        this->textResultMatrix = makeTextFromMatrix();
        this->ui->labelMatrix_2->setText(this->textResultMatrix);
    }
}

QString MainWindow::makeTextFromMatrix(){
    QString temp;
    if(this->numberOfElements < 15){
        for(int i = 0; i < this->numberOfElements; i++){
            for(int j = 0; j < this->numberOfElements; j++){
                temp.push_back(QString::number(this->matrix[i][j]));
                temp.push_back("\t");
            }
            temp.push_back("\n\n");
        }
    }
    else{
        temp = "Too large matrix!";
    }
    return temp;
}

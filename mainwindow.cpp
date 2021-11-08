#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    h = 0.1;
    xBegin = -3;
    xEnd = 3 + h;
    ui->widget->xAxis->setRange(-4, 4);
    ui->widget->yAxis->setRange(0, 9);

    N = (xEnd - xBegin)/h + 2;

    for(X = xBegin; X <= xEnd; X+=h)
    {
        x.push_back(X);
        y.push_back(X*X);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->point_table, SIGNAL(cellChanged(int, int)), this, SLOT(on_point_table_cellChanged(int, int)));
    connect(ui->point_table, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(on_point_table_currentCellChanged(int, int, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::on_point_table_cellChanged(int row, int column)
//{
//    int row_count = ui->point_table->rowCount();

//    if(row == (row_count - 1) && row_count < 12)
//    {
//        ui->point_table->setRowCount(row_count + 1);
//    }
//}

void MainWindow::on_point_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    int row_count = ui->point_table->rowCount();

    if(currentRow == (row_count - 1) && previousRow == (currentRow - 1) && row_count < 12)
    {
        ui->point_table->setRowCount(row_count + 1);
    }
}

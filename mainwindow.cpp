#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->point_table, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(on_point_table_itemChanged(QTableWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_point_table_itemChanged(QTableWidgetItem *item)
{
    int row_count = ui->point_table->rowCount();

    if(item->row() == (row_count - 1) && row_count < 12 && item->text() != "")
    {
        ui->point_table->setRowCount(row_count + 1);
    }
}

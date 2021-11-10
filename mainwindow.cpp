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

    if(item->row() == (row_count - 1) && row_count < MAX_POINTS && item->text() != "")
    {
        ui->point_table->insertRow(row_count);
    }
}

void MainWindow::on_input_Btn_clicked()
{
    std::vector<std::pair<double, double>> x_y;

    for (int i = 0; i < ui->point_table->rowCount() - 1; i++ )
    {
        auto x_text = ui->point_table->item(i, 0)->text();
        auto y_text = ui->point_table->item(i, 1)->text();

        if(x_text != "" && y_text != "")
        {
            std::pair<double, double> temp = std::make_pair(x_text.toDouble(),y_text.toDouble());
            x_y.push_back(temp);
        }

    }

}

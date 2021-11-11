#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "systemOfCubicSplines.h"

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
    QString x_text, y_text;
    double min_x, min_y, max_x, max_y;


    for (int i = 0; i < ui->point_table->rowCount() - 1; i++ )
    {


        auto x_cell = ui->point_table->item(i, 0);
        auto y_cell = ui->point_table->item(i, 1);

        if(x_cell != nullptr)
        {
            x_text = x_cell->text();
        }
        else
        {
            x_text = "";
        }

        if(y_cell != nullptr)
        {
            y_text = y_cell->text();
        }
        else
        {
            y_text = "";
        }


        if(x_text != "" && y_text != "")
        {
            double x = x_text.toDouble();
            double y = y_text.toDouble();

            if(i == 0)
            {
                max_x = x;
                max_y = y;
                min_x = x;
                min_y = y;
            }
            else
            {
                if(max_x < x) {max_x = x;}
                if(max_y < y) {max_y = y;}
                if(min_x > x) {min_x = x;}
                if(min_y > y) {min_y = y;}
            }

            std::pair<double, double> temp = std::make_pair(x,y);
            x_y.push_back(temp);
        }

    }

    if(x_y.size() < 3 )
    {
        QMessageBox::critical(0, "Ошибка", "Введите 3 или более точки");

    }
    else
    {
        systemOfCubicSplines systems(x_y);


    }

}

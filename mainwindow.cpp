#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "systemOfCubicSplines.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->point_table, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(on_point_table_itemChanged(QTableWidgetItem *)));
    ui->plot_widget->xAxis->setLabel("x");
    ui->plot_widget->yAxis->setLabel("y");
    splain_table = new splainTable;
    connect(this, &MainWindow::sendTable, splain_table, &splainTable::getTable);
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
    int row_count;

    if(ui->point_table->rowCount() == 12) {row_count = 12;}
    else {row_count = ui->point_table->rowCount() - 1;}

    for (int i = 0; i < row_count; i++ )
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

            std::pair<double, double> temp = std::make_pair(x_text.toDouble(),y_text.toDouble());
            x_y.push_back(temp);
        }

    }

    if(x_y.size() < 3 )
    {
        QMessageBox::critical(0, "Ошибка", "Введите 3 или более точки");

    }
    else
    {
        QVector<double> x_list;
        QVector<double> y_list;
        QVector<QColor> colors{QColor(0,0,0), QColor(0,255,0), QColor(0,0,255), QColor(255,0,0),
                               QColor(255,165,0), QColor(128,0,128), QColor(231,84,128), QColor(105,149,130),
                               QColor(0,0,0), QColor(0,0,255), QColor(255,0,0), QColor(0,255,0)};
        ui->plot_widget->clearGraphs();

        int k = 0;

        systemOfCubicSplines systems(x_y);
        auto list = systems.getCubicSplineList();

        double min_x, min_y, max_x, max_y;


        for(std::vector<cubicSpline>::iterator i = list.begin(); i != list.end(); i++)
        {
            ui->plot_widget->addGraph();

            double x_start, x_finish;
            if((*i).get_x1() < (*i).get_x2()){ x_start = (*i).get_x1(); x_finish = (*i).get_x2(); }
            else { x_start = (*i).get_x2(); x_finish = (*i).get_x1(); }

            for (double x = x_start; x < x_finish; x += STEP)
            {

               x_list.push_back(x);
               double y = (*i).F(x);
               y_list.push_back(y);


               if(max_x < x) {max_x = x;}
               if(max_y < y) {max_y = y;}
               if(min_x > x) {min_x = x;}
               if(min_y > y) {min_y = y;}
            }
               x_list.push_back(x_finish);
               y_list.push_back((*i).F(x_finish));

            ui->plot_widget->graph(k)->setPen(colors[k]);
            ui->plot_widget->graph(k)->addData(x_list, y_list);
            k++;
            x_list.clear();
            y_list.clear();
        }
        ui->plot_widget->xAxis->setRange(min_x - STEP, max_x + STEP);
        ui->plot_widget->yAxis->setRange(min_y - STEP, max_y + STEP);
        ui->plot_widget->replot();
    }

}

void MainWindow::on_clear_Btn_clicked()
{
    ui->point_table->clearContents();
    ui->point_table->setRowCount(1);
}

void MainWindow::on_viewSplainTable_clicked()
{
    splain_table->hide();
    emit sendTable();
    splain_table->show();
}

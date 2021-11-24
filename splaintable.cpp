#include "splaintable.h"
#include "ui_splaintable.h"

splainTable::splainTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::splainTable)
{
    ui->setupUi(this);
}

splainTable::~splainTable()
{
    delete ui;
}

void splainTable::getTable(systemOfCubicSplines system)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);
    int N = system.get_N();
    ui->tableWidget->setRowCount(N);
    auto list = system.getCubicSplineList();

    for (int i = 0; i < N; i++) {
         ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(list[i].get_a())));
         ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(list[i].get_b())));
         ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(list[i].get_c())));
         ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(list[i].get_d())));
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //read-only items on table
}

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
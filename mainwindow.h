#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAX_POINTS 12
#define STEP 0.1


#include <QMainWindow>
#include <QTableWidgetItem>
#include <splaintable.h>
#include "systemOfCubicSplines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_point_table_itemChanged(QTableWidgetItem *item);

    void on_input_Btn_clicked();

    void on_clear_Btn_clicked();

    void on_viewSplainTable_clicked();

private:
    Ui::MainWindow *ui;
    splainTable *splain_table;

signals:
    void sendTable(systemOfCubicSplines);

};
#endif // MAINWINDOW_H

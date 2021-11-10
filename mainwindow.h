#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAX_POINTS 12


#include <QMainWindow>
#include <QTableWidgetItem>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

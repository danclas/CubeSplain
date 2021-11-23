#ifndef SPLAINTABLE_H
#define SPLAINTABLE_H

#include <QWidget>

namespace Ui {
class splainTable;
}

class splainTable : public QWidget
{
    Q_OBJECT

public:
    explicit splainTable(QWidget *parent = nullptr);
    ~splainTable();

private:
    Ui::splainTable *ui;
};

#endif // SPLAINTABLE_H

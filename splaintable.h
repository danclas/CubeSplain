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

public slots:
    void slot();
};

#endif // SPLAINTABLE_H

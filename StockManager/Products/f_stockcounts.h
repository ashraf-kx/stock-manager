#ifndef F_STOCKCOUNTS_H
#define F_STOCKCOUNTS_H

#include <QFrame>

namespace Ui {
class F_StockCounts;
}

class F_StockCounts : public QFrame
{
    Q_OBJECT

public:
    explicit F_StockCounts(QWidget *parent = 0);
    ~F_StockCounts();

private:
    Ui::F_StockCounts *ui;
};

#endif // F_STOCKCOUNTS_H

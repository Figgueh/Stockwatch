#ifndef TICKERPRICEWIDGET_H
#define TICKERPRICEWIDGET_H
#include "qlabel.h"

#include <QHBoxLayout>

class TickerPriceWidget : public QHBoxLayout
{
    Q_OBJECT

private:
    QLabel *m_tickerLabel;
    QLabel *m_priceLabel;

    QLabel *buildLabel(QString text);

public:
    TickerPriceWidget(QString ticker = "", double price = 0, QWidget *parent = 0);

signals:

public slots:
    void on_changePrice(QString ticker, double price);
};

#endif // TICKERPRICEWIDGET_H

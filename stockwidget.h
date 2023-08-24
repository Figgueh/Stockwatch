#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtGui>
#include "watchlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StockWidget; }
QT_END_NAMESPACE

class StockWidget : public QMainWindow
{
    Q_OBJECT

public:
    StockWidget(QWidget *parent = nullptr);
    ~StockWidget();

    void parseData();

protected:
    // Mouse events are to make the window dragable
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::StockWidget *ui;

    QNetworkAccessManager m_manager;
    QNetworkReply *m_reply = nullptr;

    QPointF oldPos;

    watchlist m_stockList;

public slots:
    void on_update(QString ticker, double price);

signals:
    void changePrice(QString ticker, double price);

};
#endif // STOCKWIDGET_H

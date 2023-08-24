#include "stockwidget.h"
#include "./ui_stockwidget.h"
#include "watchlist.h"
#include "twelvedata.h"
#include "TickerPriceWidget.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

StockWidget::StockWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StockWidget)
{
    //Load the API
    const QString key = "7b27f8823550414cba12d2ba1375bab4";
    twelvedata *API = new twelvedata(key);

    //Load the users watchlist
    QStringList watchlist = watchlist::readList();

    ui->setupUi(this);

    foreach (QString ticker, watchlist) {
        TickerPriceWidget *price = new TickerPriceWidget(ticker);
        ui->gridLayout->addLayout(price, watchlist.indexOf(ticker) + 1, 1);

        int widgetHeight = price->layout()->sizeHint().height();

        // Resize the layout
        int layoutHeight = ui->gridLayout->layout()->sizeHint().height();
        ui->gridLayoutWidget->setFixedHeight(layoutHeight + widgetHeight);

        // Resize the main window
//        this->setFixedSize(this->width(), ui->gridLayoutWidget->size().height());
//        this->setFixedSize(this->width(), this->height() + widgetHeight);

        QObject::connect(this, &StockWidget::changePrice, price, &TickerPriceWidget::on_changePrice);
        QObject::connect(API, &twelvedata::updatePrice, price, &TickerPriceWidget::on_changePrice);

        emit changePrice(ticker, 1000);
    }

    // Resize the main window
    this->setFixedSize(this->width(), ui->gridLayoutWidget->maximumHeight() + watchlist.size() * 5);

    emit changePrice("ACB", 100);


//    API->getPrice("ACB");

}

void StockWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void StockWidget::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

void StockWidget::on_update(QString ticker, double price)
{
    emit changePrice(ticker, price);
}

StockWidget::~StockWidget()
{
    delete ui;
}


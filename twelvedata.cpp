#include "twelvedata.h"
#include "stockwidget.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

QString route::build()
{
    return this->domainName + this->query + "?symbol=" + this->symbol + "&apikey=" + this->key;
}

twelvedata::twelvedata(QString key)
{
    m_route.domainName = "https://api.twelvedata.com/";
    m_route.key = key;
}

void twelvedata::makeRequest()
{
    QString request = m_route.build();
    m_reply = m_manager.get(QNetworkRequest(request));
    connect(m_reply, &QNetworkReply::finished, this,  &twelvedata::parseData);
}

void twelvedata::parseData()
{
    if(m_reply->error() == QNetworkReply::NoError){
        QByteArray data = m_reply->readAll();
        QJsonDocument doc =  QJsonDocument::fromJson(data);
        emit updatePrice(m_route.symbol, doc["price"].toString().toDouble());
    }
}

void twelvedata::getPrice(QString ticker)
{
    //https://api.twelvedata.com/price?symbol=AAPL&apikey=your_api_key
    m_route.query = "price";
    m_route.symbol = ticker;
    makeRequest();
}


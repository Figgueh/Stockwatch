#ifndef TWELVEDATA_H
#define TWELVEDATA_H
#include "stockwidget.h"

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtGui>

struct route
{
    QString domainName;
    QString path;
    QString query;
    QString symbol;
    QString key;

    QString build();
};


class twelvedata : public QMainWindow
{
    Q_OBJECT

public:
    twelvedata(QString key);
    void makeRequest();
    void getPrice(QString ticker);
    void parseData();


private:
    route m_route;
    QNetworkAccessManager m_manager;
    QNetworkReply *m_reply = nullptr;

signals:
    void updatePrice(QString ticker, double price);
};

#endif // TWELVEDATA_H

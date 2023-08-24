#include "watchlist.h"

#include <QFile>
#include <QMessageBox>

watchlist::watchlist()
{

}

QStringList watchlist::readList()
{
    QStringList tickers ;
    QFile watchlistFile("watchlist.txt");

    if(!watchlistFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", watchlistFile.errorString());
    }

    QTextStream in(&watchlistFile);

    while(!in.atEnd()) {
        QString line = in.readLine();
        tickers.append(line);
    }

    watchlistFile.close();
    return tickers;
}

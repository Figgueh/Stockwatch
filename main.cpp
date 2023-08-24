#include "stockwidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "StockWatch_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    StockWidget w;

    // Setup the window
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground, true);
    w.setFixedSize(w.width(), w.height());


    w.show();
    return a.exec();
}

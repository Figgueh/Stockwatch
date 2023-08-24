#include "TickerPriceWidget.h"
#include "qgraphicsgloweffect.h"
#include <QString>


QLabel *TickerPriceWidget::buildLabel(QString text)
{
    QLabel *label = new QLabel();
    label->setText(text);

    // Change size
    QFont font = label->font();
    font.setPointSize(14);
    font.setWeight(QFont::DemiBold);
    label->setFont(font);

    // Apply glow
    QGraphicsGlowEffect * glow = new QGraphicsGlowEffect();
    glow->setStrength(5);
    glow->setBlurRadius(6);
    label->setGraphicsEffect(glow);

    // Add extra margine to not cut off glow
    label->setMargin(10);

    return label;
}


TickerPriceWidget::TickerPriceWidget(QString ticker, double price, QWidget *parent)
    : QHBoxLayout(parent)
{
    m_tickerLabel = buildLabel(ticker);
    this->addWidget(m_tickerLabel);

    QSpacerItem *horizonalSpace = new QSpacerItem(50, 10);
    this->addItem(horizonalSpace);

    m_priceLabel = buildLabel(QString::number(price));
    this->addWidget(m_priceLabel);
}

void TickerPriceWidget::on_changePrice(QString ticker, double price)
{
    if(m_tickerLabel->text() == ticker)
        m_priceLabel->setText(QString::number(price, 'g', 14));
}

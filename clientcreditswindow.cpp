#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>

#include "client.h"
#include "ibanksystemmodel.h"
#include "clientcreditswindow.h"
#include "credit.h"

ClientCreditsWindow::ClientCreditsWindow(IBankSystemModel *bankSystemModel, Client *client)
{
    this->client = client;
    this->bankSystemModel = bankSystemModel;

    setWindowTitle("Управление кредитами");
    setFixedWidth(300);
    setFixedHeight(300);

    QLabel *creditsListLabel = new QLabel("Список кредитов:", this);

    creditsListWidget = new QListWidget(this);
    creditsListWidget->addItem("2942049");

    connect(creditsListWidget, &QListWidget::itemClicked, this, &ClientCreditsWindow::changeCurrentCreditId);

    QPushButton *showInfo = new QPushButton("Информация о кредите", this);
    connect(showInfo, &QPushButton::clicked, this, &ClientCreditsWindow::showCreditInfo);

    QPushButton *takeLoan = new QPushButton("Взять кредит", this);
    connect(takeLoan, &QPushButton::clicked, this, &ClientCreditsWindow::takeLoan);

    QPushButton *makeMonthlyPayment = new QPushButton("Совершить платёж по кредиту", this);
    connect(makeMonthlyPayment, &QPushButton::clicked, this, &ClientCreditsWindow::makeMonthlyPayment);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(creditsListLabel, 0, 0);
    gridLayout->addWidget(creditsListWidget, 1, 0);
    gridLayout->addWidget(showInfo, 2, 0);
    gridLayout->addWidget(takeLoan, 3, 0);
    gridLayout->addWidget(makeMonthlyPayment, 4, 0);
}

void ClientCreditsWindow::changeCurrentCreditId(QListWidgetItem *item)
{
    qDebug() << "before:\n";
    qDebug() << "currentCreditId = " << currentCreditId << "\n";
    currentCreditId = item->text().toInt();
    qDebug() << "after:\n";
    qDebug() << "currentCreditId = " << currentCreditId << "\n";
}

int64_t ClientCreditsWindow::getCurrentCreditId() const
{
    if (currentCreditId < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать кредит в списке");
        msgBox.exec();
        return -1;
    }
    return currentCreditId;
}

void ClientCreditsWindow::showCreditInfo()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("аалывал");
    msgBox.setText("гыыыыы");
    msgBox.exec();
}

void ClientCreditsWindow::makeMonthlyPayment()
{
    // как только всё выплачено, статус кредита должен поменяться с ACTIVE на REPAID
    QMessageBox msgBox;
    msgBox.setWindowTitle("aaaa");
    msgBox.setText("гыыыыы");
    msgBox.exec();
}

void ClientCreditsWindow::takeLoan()
{
    QInputDialog inpDialog;
    QStringList alternatives;

    alternatives.append("3 месяца");
    alternatives.append("6 месяцев");
    alternatives.append("12 месяцев");
    alternatives.append("24 месяца");
    alternatives.append("более 24 месяцев");
    QString choice = inpDialog.getItem(this, "Срок кредита", "Выберите срок кредита", alternatives, 0, false);

    int months = 0;

    if (choice == alternatives[0])      { months = 3; }
    else if (choice == alternatives[1]) { months = 6; }
    else if (choice == alternatives[2]) { months = 12; }
    else if (choice == alternatives[3]) { months = 24; }
    else
    {
        // 96 месяцев - самый максимум
        bool ok = false;

        do
        {
            months = inpDialog.getInt(this, "Срок кредита", "Введите срок кредита в месяцах", 25, 25, 96, 1, &ok);
        }
        while (!ok);
    }

    Currency currency = client->isFromRB() ? BYN : US_DOLLAR;
    // from 100.00$ to 10000.00$
    CurrencyConverter converter;
    double minValue = converter.convert(MIN_CREDIT_VALUE, US_DOLLAR, currency);
    double maxValue = converter.convert(MAX_CREDIT_VALUE, US_DOLLAR, currency);
    QString currencyStr = currency == BYN ? "BYN" : "$";

    QString prompt = "Введите сумму кредита (" + currencyStr + "): " + QString::number(minValue) + " - " +
            QString::number(maxValue);

    bool ok = false;
    double value = minValue;

    do
    {
        value = inpDialog.getDouble(this, "Сумма кредита", prompt, minValue, minValue, maxValue, 2, &ok);
    }
    while (!ok);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация");
    QString text = "Вы берёте кредит на " + QString::number(months) + " месяцев\n";
    text += "Сумма кредита: " + QString::number(value) + " " + currencyStr + "\n";
    double percentRate = computePercentRate(months);
    text += "Процентная ставка: " + QString::number(percentRate) + " % в месяц\n";
    msgBox.setText(text);
    msgBox.exec();
}

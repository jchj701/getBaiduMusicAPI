#include "mainwindowfornet.h"
#include <QApplication>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QNetworkCookieJar *cookJar = new QNetworkCookieJar();

    MainWindowForNet w(nullptr, cookJar);

    w.show();

    return a.exec();
}

#ifndef GETBAIDUCHANNEL_H
#define GETBAIDUCHANNEL_H

#include <QGridLayout>
#include <QFrame>
#include <QPushButton>
#include <QString>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkCookieJar>

typedef struct _CHANNEL_INFO
{
    QString channelId;
    QString channelName;
}CHANNEL_INFO;

class GetBaiduChannel : public QFrame
{
    Q_OBJECT

public:
    explicit GetBaiduChannel(QFrame *parent = nullptr, QNetworkCookieJar *cookie = nullptr);
    QList<CHANNEL_INFO> getMusicChannel();  //从网络获取音频频道

private:
    QNetworkCookieJar *m_cookJar;  // cookie对象

};

#endif // GETBAIDUCHANNEL_H

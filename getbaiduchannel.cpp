#include "getbaiduchannel.h"

const QString channelUrl = "http://fm.taihe.com/dev/api/?tn=channellist";

GetBaiduChannel::GetBaiduChannel(QFrame *parent, QNetworkCookieJar *cookie)
{
    m_cookJar = cookie;
}

QList<CHANNEL_INFO> GetBaiduChannel::getMusicChannel()
{
    QList <CHANNEL_INFO> channelInfoList;

    //HTTP请求
    QNetworkRequest networkRequest;
    //管理HTTP交互过程
    QNetworkAccessManager *networkManager = new QNetworkAccessManager; //管理HTTP交互过程

    //构建HTTP请求头
    networkRequest.setUrl (QUrl(channelUrl));
    //设置COOKIE
    networkManager->setCookieJar (m_cookJar);

    //发送http请求
    QNetworkReply *reply = networkManager->get (networkRequest);

    // 事件循环     quit() 终止
    QEventLoop loop;

    //接收完服务器发送过来的数据后退出
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    //事件循环，等待结束
    loop.exec();

    //下一次主消息循环收到这个event之后才会销毁对象
    reply->deleteLater();

//定义变量，存储html
    //获取所有页面信息
    QByteArray buf = reply->readAll();
    //qDebug() << "buf =" <<buf;

    QJsonParseError jsonError; //用于在 JSON 解析中报告错误
    //构建 JSON 文档                           转化为 JSON 文档
    QJsonDocument jsonRes = QJsonDocument::fromJson(buf, &jsonError);

    if(jsonError.error == QJsonParseError::NoError)
    {//没有错误
        if(jsonRes.isObject ())
        {
            //json转换成map
            QVariantMap result = jsonRes.toVariant ().toMap ();

            //遍历所有音乐频道列表
            foreach(QVariant channel, result["channel_list"].toList ())
            {
                QVariantMap channelMap = channel.toMap ();

                CHANNEL_INFO channelInfo;
                channelInfo.channelId = channelMap["channel_id"].toString();
                channelInfo.channelName = channelMap["channel_name"].toString ();

                //存储入频道信息列表
                channelInfoList.append(channelInfo);
            }
        }
    }

    //返回得到的所有频道列表(id/name)
    return channelInfoList;
}

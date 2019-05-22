#include "getsongplaylistid.h"

const QString playListUrl = "http://fm.taihe.com/dev/api/?tn=playlist&format=json&id=";
GetSongPlayListId::GetSongPlayListId(QObject *parent, QNetworkCookieJar *cookie) : QObject(parent)
{
    m_cookJar = cookie;
}

QList<QString> GetSongPlayListId::getSongIdList(QString channelId)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    networkRequest.setUrl (QUrl(playListUrl + channelId));

    networkManager->setCookieJar (m_cookJar);

    QNetworkReply *reply = networkManager->get (networkRequest);

    QEventLoop loop;
    connect (reply, SIGNAL (finished()), &loop, SLOT (quit()));
    loop.exec ();
    reply->deleteLater ();

    QList <QString> songId;
    QByteArray buf = reply->readAll ();

    QJsonParseError jsonError;
    QJsonDocument jsonRes = QJsonDocument::fromJson (buf, &jsonError);
    //qDebug() << "jsonError.error = " << jsonError.error;
    //qDebug() << "jsonRes = " << jsonRes;

    if(jsonError.error == QJsonParseError::NoError)
    {
        QVariantMap result = jsonRes.toVariant ().toMap ();
        qDebug() << "result = " << result;

        foreach(QVariant song, result["list"].toList ())
        {
            QVariantMap songMap = song.toMap ();

            QString id = songMap["id"].toString ();

            if(!id.isEmpty ())
            {
                songId.append (id);
            }
        }
    }

    return songId;
}

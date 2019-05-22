#include "getsongreallink.h"

const QString downLoadLinkUrl = "http://music.taihe.com/song/";

GetSongRealLink::GetSongRealLink(QObject *parent, QNetworkCookieJar *cookie) : QObject(parent)
{
    m_cookJar = cookie;
}

SONG_INFO GetSongRealLink::getSongRealLinkById (QString songId)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl (QUrl(downLoadLinkUrl + songId));
    networkManager.setCookieJar(m_cookJar);

    QNetworkReply *reply = networkManager.get (networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();

    QByteArray buf = reply->readAll ();

    SONG_INFO songInfo;

    QJsonParseError jsonError;
    QJsonDocument jsonRes = QJsonDocument::fromJson (buf, &jsonError);

    if(jsonError.error == QJsonParseError::NoError)
    {
        if(jsonRes.isObject ())
        {
            //转map
            QVariantMap result = jsonRes.toVariant ().toMap ();
            QVariantMap dataList = result["data"].toMap ();
            qDebug() << "转字典ing";
            //遍历
            foreach(QVariant data, dataList["songList"].toList ())
            {
                QVariantMap linkMap = data.toMap ();

                songInfo.songRealLink = linkMap["songLink"].toString ();
                songInfo.songName = linkMap["songName"].toString ();
                songInfo.artistName = linkMap["artistName"].toString();
                //歌手图片（小图片，还要大图标）
                songInfo.songPicSmall = linkMap["songPicSmall"].toString();
                songInfo.songPicRadio = linkMap["songPicRadio"].toString();
                //专辑名称
                songInfo.albumName = linkMap["albumName"].toString();
                //歌词链接
                songInfo.lrcLink = linkMap["lrcLink"].toString();
            }
        }
    }

    return songInfo;
}

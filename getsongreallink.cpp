#include "getsongreallink.h"

const QString downLoadLinkUrl = "http://music.taihe.com/song/";
//const QString downLoadLinkUrl1 = "http://songsearch.kugou.com/song_search_v2?keyword=%E5%91%A8%E6%9D%B0%E4%BC%A6&page=&pagesize=&userid=-1&clientver=&platform=WebFilter&tag=em&filter=2&iscorrection=1&privilege_filter=0";
GetSongRealLink::GetSongRealLink(QObject *parent, QNetworkCookieJar *cookie) : QObject(parent)
{
    m_cookJar = cookie;
}

SONG_INFO GetSongRealLink::getSongRealLinkById (QString songId)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl (QUrl(downLoadLinkUrl + songId));
    //networkRequest.setUrl (QUrl(downLoadLinkUrl1));
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

                //链接地址
                songInfo.songRealLink = linkMap["songLink"].toString();
                //歌曲名
                songInfo.songName = linkMap["songName"].toString();
                //歌手
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

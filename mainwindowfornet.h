#ifndef MAINWINDOWFORNET_H
#define MAINWINDOWFORNET_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMainWindow>
#include <QNetworkCookieJar>
#include <QSettings>
#include "getbaiduchannel.h"
#include "getsongplaylistid.h"
#include "getsongreallink.h"

namespace Ui {
    class MainWindowForNet;
    }

class MainWindowForNet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForNet(QWidget *parent = nullptr, QNetworkCookieJar *cookieJar = nullptr);
    ~MainWindowForNet();

    //获得频道列表，频道信息（id，name）
    QList<CHANNEL_INFO> getChannelList();

public slots:
    //槽函数，频道选择。 必须实现
    void channelSelected(int iChannel);

signals:   //只需要声明，不用实现
    //信号函数， 主动emit
    void channelChanged(CHANNEL_INFO Channel);

private:
    Ui::MainWindowForNet *ui;
    GetBaiduChannel *m_getBaiduChannel;  //  通过网络获得频道信息 HTTP请求响应/解析
    QList<CHANNEL_INFO> m_channelList;     //频道列表
    int m_iLastChannelIndex;            //上一次播放的频道下标

    QGridLayout *m_gridlayOut;          //网格布局
    QButtonGroup m_btnGroup;            //工具按钮组件（多个）
    QWidget *tempwidget;

    GetSongPlayListId *m_getsonglistid;
    GetSongRealLink *m_getsongreallink;
    SONG_INFO songInfo;
};

#endif // MAINWINDOWFORNET_H

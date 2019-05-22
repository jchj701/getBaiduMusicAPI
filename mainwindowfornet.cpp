#include "mainwindowfornet.h"
#include "ui_mainwindowfornet.h"

#include <QGridLayout>
#include "getbaiduchannel.h"
#include "getsongplaylistid.h"
#include "getsongreallink.h"

MainWindowForNet::MainWindowForNet(QWidget *parent, QNetworkCookieJar *cookieJar) :
    QMainWindow(parent),
    ui(new Ui::MainWindowForNet)
{
    ui->setupUi(this);

    m_getBaiduChannel = new GetBaiduChannel(nullptr, cookieJar);
    m_channelList = getChannelList ();

    m_gridlayOut = new QGridLayout;

    for (int i = 0, k = 0; i < m_channelList.size ()/4; i++, k += 4)
    {
        for (int j = 0; j < 4; j++)
        {
            QPushButton *btn = new QPushButton(this);

            btn->setText (m_channelList.at (k + j).channelName);
            qDebug() << "m_channelList.at(k + j).channelName" <<m_channelList.at(k + j).channelName;

            m_gridlayOut->addWidget (btn, i, j);

            m_btnGroup.addButton (btn, k + j);
            qDebug() << "m_channelList.at(k + j).channelName" <<m_channelList.at(k + j).channelName;
        }
    }

    tempwidget = new QWidget(this);
    tempwidget->setLayout (m_gridlayOut);
    setCentralWidget (tempwidget);

    connect (&m_btnGroup, SIGNAL (buttonClicked(int)), this, SLOT (channelSelected(int)));
    m_iLastChannelIndex = 0;
    m_getsonglistid = new GetSongPlayListId(nullptr, cookieJar);
    m_getsongreallink = new GetSongRealLink(nullptr, cookieJar);
}

MainWindowForNet::~MainWindowForNet()
{
    delete ui;
}

QList<CHANNEL_INFO> MainWindowForNet::getChannelList()
{
    m_channelList = m_getBaiduChannel->getMusicChannel ();

    return m_channelList;
}

void MainWindowForNet::channelSelected (int iChannel)
{
    qDebug() << "Channel = " << iChannel;
    QList<QString> songId = m_getsonglistid->getSongIdList (QString::number(iChannel));
    qDebug() << "songId = " << songId.first ();
    m_getsongreallink->getSongRealLinkById(songId.first ());



}

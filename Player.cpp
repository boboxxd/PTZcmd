//
// Created by hhit on 18-3-26.
//

#include "Player.h"
#include <QDebug>
#include <QTime>
Player::Player()
{

}

Player::Player(const LoginInfo& info)
{
    m_ip=info.ip;
    m_port=info.port;
    m_user=info.user;
    m_passwd=info.passwd;
    m_presetnum=info.presetnum;
}

void Player::init()
{
    //初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    NET_DVR_SetCapturePictureMode(1);
}


bool Player::start()
{
    // 注册设备
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30(m_ip.toLocal8Bit().data(),m_port, m_user.toLocal8Bit().data(), m_passwd.toLocal8Bit().data(), &struDeviceInfo);
    if (lUserID < 0)
    {
        NET_DVR_Cleanup();
        return false;
    }

    //设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL,g_ExceptionCallBack, NULL);
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    //struPlayInfo.hPlayWnd = (HWND)m_wigetID; //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    struPlayInfo.hPlayWnd = 0;
    struPlayInfo.lChannel  = 1;//预览通道号
    struPlayInfo.dwStreamType = 0; //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 0; //0- 非阻塞取流,1- 阻塞取流
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, NULL, NULL);
    if (lRealPlayHandle < 0)
    {
        printf("NET_DVR_RealPlay_V40 error,%d\n",NET_DVR_GetLastError());
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return false;
    }
    return true;
}

QString Player::Ip()
{
    return m_ip;
}

void Player::stop()
{
    NET_DVR_StopRealPlay(lRealPlayHandle);
    NET_DVR_Logout(lUserID);
    NET_DVR_Cleanup();
    printf("%s 断开连接！\n", m_ip.toStdString().data());
}

void Player::CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    char tempbuf[256] = {0};
    switch(dwType)
    {
        case EXCEPTION_RECONNECT:
//预览时重连
           // printf("----------reconnect--------%d\n", time(NULL));
            break;
        default:
            break;
    }
}

void Player::setLoginInfo(const LoginInfo& info)
{
    m_ip=info.ip;
    m_port=info.port;
    m_user=info.user;
    m_passwd=info.passwd;
    m_presetnum=info.presetnum;
}


void Player::ptzPreset(int p)
{
    bool ret;
    ret=NET_DVR_PTZPreset(lRealPlayHandle,GOTO_PRESET,p);
    if(ret)
    {

    }
}

void Player::captureimage(QString output)
{
    NET_DVR_JPEGPARA JpegPara{19,1};
    NET_DVR_CaptureJPEGPicture( lUserID, 1,  &JpegPara, QString("%1/%2.jpeg").arg(output).arg(QTime::currentTime().toString("hhmmsszzz")).toLocal8Bit().data());
}


int Player::presetcounts()
{
    return m_presetnum;
}


Player::~Player()
{

}



//
// Created by hhit on 18-3-26.
//

#ifndef DVRPTZ_PLAYER_H
#define DVRPTZ_PLAYER_H
#include "HCNetSDK.h"
#include <QObject>
typedef QT_PREPEND_NAMESPACE(quintptr) WId;


struct LoginInfo{
    QString ip;
    int port;
    QString user;
    QString passwd;
    int presetnum;
};

class Player{
public:
    Player();
    Player(const LoginInfo&);
    void init();
    bool start();
    void stop();
    ~Player();
    void setLoginInfo(const LoginInfo&);
    //void setWindow( WId wigetID);
    void ptzPreset(int p);   //预置点操作
    void captureimage(QString output);
    int presetcounts();
    QString Ip();
private:
    //异常回调
    static void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
    WId m_wigetID;

    QString m_ip;
    int m_port;
    QString m_user;
    QString m_passwd;
    int m_presetnum;

    LONG lUserID;
    LONG lRealPlayHandle;//预览句柄点
};







#endif //DVRPTZ_PLAYER_H

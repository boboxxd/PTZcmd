//
// Created by hhit on 18-3-28.
//

#include "Control.h"
#include <iostream>
#include <QDir>
#include <QMutex>
using namespace std;

static QMutex mutex;

LoginInfo adapterto(const ValueInfo &info)
{
    LoginInfo t;
    t.ip=info.ip;
    t.port=info.port;
    t.user=info.user;
    t.passwd=info.passwd;
    t.presetnum=info.presetnum;
    return t;
}

static ostream& hout(ostream &os)
{
    mutex.lock();
    os<<QTime::currentTime().toString("[hh:mm:ss:zzz] ").toStdString();
    mutex.unlock();
    return os;
}

Control::Control()
{
    setting=new Setting("config.ini");
}


void Control::Registerplayer()
{
    for(int i=0;i<setting->count();i++)
    {
        ValueInfo Info(setting->read(i));
        Player player(adapterto(Info));
        player.init();
        if(!player.start())
        {
            hout(cout)<<QString("设备%1:%2 注册失败！").arg(Info.id).arg(Info.ip).toStdString()<<endl;
            std::ofstream logout("log.txt",ios::out|ios::app);
            hout(logout)<<QString("设备%1:%2 注册失败！").arg(Info.id).arg(Info.ip).toStdString()<<endl;
            continue;
        }

        players[Info.id]=player;
        hout(cout)<<QString("设备%1:%2 注册完毕！").arg(Info.id).arg(Info.ip).toStdString()<<endl;
        std::ofstream logout("log.txt",ios::out|ios::app);
        hout(logout)<<QString("设备%1:%2 注册完毕！").arg(Info.id).arg(Info.ip).toStdString()<<endl;
    }
}


bool Control::TurnTo(int playerid,int position)//x射线机 转到位置x
{
    players[playerid].ptzPreset(position);
    hout(cout)<<QString("设备%1:转动至位置%2！").arg(playerid).arg(position).toStdString()<<endl;
    std::ofstream logout("log.txt",ios::out|ios::app);
    hout(logout)<<QString("设备%1:转动至位置%2！").arg(playerid).arg(position).toStdString()<<endl;
}

bool Control::CaptureImage(int playerid)
{
    ValueInfo Info(setting->read(playerid));
    //创建文件夹
    if(!QDir(Info.output).exists())
    {
        QDir t;
        t.mkdir(Info.output.toLocal8Bit().data());
    }

    players[playerid].captureimage(Info.output);
    hout(cout)<<QString("设备%1:截图完毕！").arg(playerid).toStdString()<<endl;
    std::ofstream logout("log.txt",ios::out|ios::app);
    hout(logout)<<QString("设备%1:截图完毕！").arg(playerid).toStdString()<<endl;
}


bool Control::CloseAll()
{
    for(auto i=players.begin();i!=players.end();i++)
    {
        i->stop();
    }
}

void Control::AvailablePlayers()
{
    cout<<endl;
    cout<<string('#',20)<<endl;
    hout(cout)<<endl<<"可用设备:\n";
    for(auto i=players.begin();i!=players.end();i++)
    {
        cout<<QString("设备%1:%2").arg(i.key()).arg(i.value().Ip()).toStdString()<<endl;
    }
    cout<<string('#',20)<<endl;
    cout<<endl;
}

int Control::playercounts()
{
    return players.count();
}

Control::~Control()
{
    delete setting;
    setting= nullptr;
}

Player& Control::player(int id)
{
    return players[id];
}


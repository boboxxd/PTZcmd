//
// Created by hhit on 18-3-28.
//
#include "Setting.h"
#include <iostream>
using namespace std;

 void printInfo(const ValueInfo& info)
{
    cout<<"id: "<<info.id<<endl;
    cout<<"ip: "<<info.ip.toStdString()<<endl;
    cout<<"port: "<<info.port<<endl;
    cout<<"user: "<<info.user.toStdString()<<endl;
    cout<<"passward: "<<info.passwd.toStdString()<<endl;
    cout<<"presetnum:"<<info.presetnum<<endl;
    cout<<"output: "<<info.output.toStdString()<<endl;
}


Setting::Setting(QString filename)
{
    if(filename !="")
    {
        m_file=filename;
        m_tool=new QSettings(m_file,QSettings::IniFormat);
        if(!QFile(m_file).exists())
        {
            init();
        }
    }
}


ValueInfo Setting::read(int id)
{
    QString Key= QString("cam_%1").arg(id);
    if( !m_tool->childGroups().contains(Key))
    {
        cout<<QString("设备id: %1 未配置！").arg(Key).toStdString()<<endl;
        return ValueInfo();
    }

    m_tool->beginGroup(Key);
    ValueInfo info;
    info.id=m_tool->value("id").toInt();
    info.ip=m_tool->value("ip").toString();
    info.port=m_tool->value("port").toInt();
    info.user=m_tool->value("user").toString();
    info.passwd=m_tool->value("passward").toString();
    info.output=m_tool->value("output").toString();
    info.presetnum=m_tool->value("presetnum",1).toInt();
    m_tool->endGroup();
    return info;
}


//初始化
void Setting::init()
{
    m_tool->beginGroup("cam_0");
    m_tool->setValue("id", 0);
    m_tool->setValue("ip", "122.192.0.173");
    m_tool->setValue("port",8000);
    m_tool->setValue("user","admin");
    m_tool->setValue("passward","ad53937301");
    m_tool->setValue("output","./output/");
    m_tool->setValue("presetnum",1);
    m_tool->endGroup();
}


int Setting::count()
{
    return m_tool->childGroups().size();
}


Setting::~Setting()
{
    delete m_tool;
}
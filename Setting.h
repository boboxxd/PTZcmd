//
// Created by hhit on 18-3-28.
//

#ifndef PTZCMD_SETTING_H
#define PTZCMD_SETTING_H

#include <QSettings>
#include <QFile>
#include <QDebug>

struct ValueInfo
{
    int id;
    QString ip;
    int port;
    QString user;
    QString passwd;
    QString output;
    int presetnum;
};

class Setting {
public:
    Setting(QString filename="");
    ~Setting();
    ValueInfo read(int id);
    int count();
private:
    void init();
    QSettings *m_tool;
    QString m_file;
};


void printInfo(const ValueInfo& info);
#endif //PTZCMD_SETTING_H

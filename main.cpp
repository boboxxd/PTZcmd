#include <QCoreApplication>
#include "Control.h"
#include <QThread>

class WorkThread:public QThread
{
public:
    WorkThread(int deviceid,Control &con)
    {
        this->deviceid=deviceid;
        this->con=con;
    }

    void run()
    {
        for(int i=0;i<con.player(deviceid).presetcounts();i++)
        {
            con.TurnTo(deviceid,i);
            sleep(8);
            con.CaptureImage(deviceid);

//            if(i==con.player(deviceid).presetcounts()-1)
//            {
//                i=-1;
//                continue;
//            }

        }
    }
private:
    int deviceid;
    Control con;
};

//ptzcmd -t 4
int main(int argc, char *argv[])
{
    Control con;
    con.Registerplayer();
    con.AvailablePlayers();

    for(int i=0;i<con.playercounts();i++)
    {
        WorkThread wthread(i,con);
        wthread.start();
        wthread.wait();
    }

    con.CloseAll();
    return 0;
}

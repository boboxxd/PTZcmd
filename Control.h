//
// Created by hhit on 18-3-28.
//

#ifndef PTZCMD_CONTROL_H
#define PTZCMD_CONTROL_H
#include "Setting.h"
#include <Player.h>
#include <QTime>
#include <ostream>
#include <fstream>
using namespace std;

LoginInfo adapterto(const ValueInfo&);
class Control {
public:
    Control();
    void AvailablePlayers();
    void Registerplayer();
    bool TurnTo(int playerid,int position);//x射线机 转到位置x
    bool CaptureImage(int playerid);
    bool CloseAll();
    Player& player(int id);
    int playercounts();
    ~Control();
private:
    QMap<int,Player> players;
    Setting *setting;
};


#endif //PTZCMD_CONTROL_H

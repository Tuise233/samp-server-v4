#define MAX_VEHICLE_ID_CHANGES 5
new sLdz;
static LastVehicleID[MAX_PLAYERS];
static VehicleIDChanges[MAX_PLAYERS];
static VehicleIDChangeTime[MAX_PLAYERS];

forward CheatTips(playerid,str[]);
public CheatTips(playerid,str[])
{
    new string[1024];
    format(string,sizeof(string),"[T-AntiCheat]%s",str);
    if(playerid == -1){
        for(new i=0;i<MAX_PLAYERS;i++){
            SendClientMessage(i, COLOR_RED, string);
        }
        return 1;
    }
    SendClientMessage(playerid,COLOR_RED,string);
    return 1;
}


forward anticheat_OnGameModeInit();
public anticheat_OnGameModeInit()
{
    SetTimer("AntiRPWeapon",100,1);
    SetTimer("AntiUnLogin",1000,1);
    //SetTimer("AntiBot",1000,1);
    sLdz = GangZoneCreate(-245.219146,1489.957397,-405.205963,1596.486938);
    SetTimer("VehicleAqq",500,1);
    return;
}

//�ؾ߰�ȫ���ж�
forward VehicleAqq();
public VehicleAqq()
{
    new Float:x,Float:y,Float:z;
    new name[64],string[256];
    new banVehicle[] = {403,406,443,432,514,515,524,532,573,449,537,538,569,570,590,430,446,452,453,454,472,473,383,393,539,595,417,425,447,460,469,476,487,488,497,511,512,513,519,520,548,553,563,577,592,593};
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(IsPlayerConnected(i))
        {
            if(GetPVarInt(i,"is_rp")) continue;
            if(GetPlayerVirtualWorld(i) == 0)
            {
                if(IsPlayerInAnyVehicle(i))
                {
                    if(GetPlayerVehicleSeat(i) == 0)
                    {
                        GetPlayerPos(i,x,y,z);
                        //�״�վ
                        //-245.219146,1489.957397,75.229408
                        //-405.205963,1596.486938,71.170364
                        if(x>-405.205963 && x < -245.219146 && y > 1489.957397 && y < 1596.486938)
                        {
                            GetPlayerName(i,name,sizeof(name));
                            for(new k=0;k<sizeof(banVehicle);k++)
                            {
                                if(banVehicle[k] == GetVehicleModel(GetPlayerVehicleID(i)))
                                {
                                    format(string,sizeof(string),"[T-AntiCheat]���%s(%d)��ʻ��IDΪ%d�İ�ȫ����ֹ��ʻ���ؾ߽����״�վ��ȫ��,�ѱ�ϵͳ�Զ�ɾ��",name,i,GetVehicleModel(GetPlayerVehicleID(i)));
                                    SendClientMessageToAll(COLOR_RED,string);
                                    SendClientMessage(i,COLOR_RED,"[T-AntiCheat]������ͨ�� /aqq ���鿴��ͼ�İ�ȫ��");
                                    //��ȡ����
                                    for(new j=0;j<MAX_PLAYERS;j++)
                                    {
                                        if(PlayerVehicle[j]== GetPlayerVehicleID(i))
                                        {
                                            if(i != j)
                                            {
                                                format(string,sizeof(string),"[T-AntiCheat]����ؾ����ڱ����%s(%d)��ʻ�Ž��밲ȫ��,Ŀǰ�ѱ�ɾ��,���������������ؾ�",name,i);
                                                SendClientMessage(j,COLOR_RED,string);
                                            }
                                            PlayerVehicle[j] = -1;
                                            DestroyVehicle(GetPlayerVehicleID(i));
                                        }
                                    }
                                }
                            } 
                        }
                    }
                }
            }
        }
    }
    return 1;
}

COMMAND:aqq(playerid)
{
    if(!GetPVarInt(playerid,"is_aqq"))
    {
        SetPVarInt(playerid,"is_aqq",233);
        SendClientMessage(playerid,COLOR_GREEN,"[������]��Ϊ���򿪷�������ȫ����Χ(���̹��л�)");
        SendClientMessage(playerid,COLOR_GREEN,"[������]�ٴ����� /aqq ���ر���ʾ");
        GangZoneShowForPlayer(playerid,sLdz,0x1AE694C8);
        GangZoneFlashForPlayer(playerid,sLdz,0xFFFF80C8);
    }
    else
    {
        DeletePVar(playerid, "is_aqq");
        SendClientMessage(playerid,COLOR_GREEN,"[������]��Ϊ���رշ�������ȫ����Χ");
        SendClientMessage(playerid,COLOR_GREEN,"[������]�ٴ����� /aqq ��������ʾ");
        GangZoneHideForPlayer(playerid, sLdz);
    }
    return 1;
}

forward AntiRPWeapon();
public AntiRPWeapon()
{
    new bangun[] = {35,36,37,38,39,40};
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(GetPlayerWeapon(i) == 44 || GetPlayerWeapon(i) == 45)
        {
            new name[64],string[256];
            GetPlayerName(i,name,sizeof(name));
            format(string,sizeof(string),"���%s(%d)��RPģʽ��Я��Υ������,�ѱ�ϵͳ���ز��߳�������",name,i);
            CheatTips(-1,string);
            ResetPlayerWeapons(i);
            Kick(i);
        }
        if(GetPVarInt(i,"is_rp"))
        {
            for(new j=0;j<5;j++)
            {
                if(GetPlayerWeapon(i) == bangun[j])
                {
                    new name[64],string[256];
                    GetPlayerName(i,name,sizeof(name));
                    format(string,sizeof(string),"���%s(%d)��RPģʽ��Я��Υ������,�ѱ�ϵͳ����",name,i);
                    CheatTips(-1,string);
                    ResetPlayerWeapons(i);
                }
            }
        }
    }
    return 1;
}


forward OnAntiCheatLagTroll(playerid);
public OnAntiCheatLagTroll(playerid)
{
    new name[64],string[256];
    GetPlayerName(playerid,name,sizeof(name));
    format(string,sizeof(string),"���%s(%d)ʹ�õ�������������ɧ�����,�ѱ�ϵͳ���ز��߳�������",name,playerid);
    CheatTips(-1,string);
    Kick(playerid);
    return 1;
}

forward anticheat_OnPlayerUpdate(playerid);
public anticheat_OnPlayerUpdate(playerid)
{
    new vid = GetPlayerVehicleID(playerid);
    if(vid > 0)
    {
        if(vid != LastVehicleID[playerid])
        {
            if(GetTickCount() - VehicleIDChangeTime[playerid] < 5000)
            {
                VehicleIDChanges[playerid]++;
                if(VehicleIDChanges[playerid] > MAX_VEHICLE_ID_CHANGES)
                {
                    CallLocalFunction("OnAntiCheatLagTroll", "i", playerid);
                    return 0;
                }
            }
            else
            {
                VehicleIDChanges[playerid] = 1;
            }
            LastVehicleID[playerid] = vid;
            VehicleIDChangeTime[playerid] = GetTickCount();
        }
    }
    return 1;
}

forward AntiUnLogin();
public AntiUnLogin()
{
    new name[64],string[256];
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(!GetPVarInt(i,"is_login"))
        {
            if(!GetPVarInt(i,"is_unlogin"))
            {
                SetPVarInt(i,"is_unlogin",1);
            }
            else
            {
                if(GetPVarInt(i,"is_unlogin") == 20)
                {
                    GetPlayerName(i,name,sizeof(name));
                    format(string,sizeof(string),"���%s(%d)����20��δ��¼,�ѱ�ϵͳ�߳�",name,i);
                    CheatTips(-1,string);
                    Kick(i);
                }
                else
                {
                    format(string,sizeof(string),"��������%d���ڵ�¼������,���򽫱�ϵͳ�߳�",20-GetPVarInt(i,"is_unlogin"));
                    SetPVarInt(i,"is_unlogin",GetPVarInt(i,"is_unlogin")+1);
                    CheatTips(i,string);
                }
            }
        }
    }
    return 1;
}

forward AntiVehicle();
public AntiVehicle()
{
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(IsPlayerConnected(i))
        {
            if(GetPlayerVirtualWorld(i) == 0)
            {
                if(GetPlayerVehicleSeat(i) == 0 )
                {
                    new vehBan[] = {403, 406, 407, 408, 417, 425, 432, 433, 435, 443, 450, 455, 478, 486, 520, 524, 532, 544, 569, 570, 584, 590, 591, 592};
                    for(new j=0;j<24;j++)
                    {
                        if(GetVehicleModel(GetPlayerVehicleID(i)) == vehBan[j])
                        {
                            new name[64],string[256];
                            GetPlayerName(i,name,sizeof(name));
                            format(string,sizeof(string),"[T-AntiCheat]���%s(%d)�ڴ������ʻΥ���ؾ�(ID%d),�ѱ�ϵͳ���ز��߳�������",name,i,GetVehicleModel(GetPlayerVehicleID(i)));
                            SendClientMessageToAll(COLOR_RED, string);
                            Kick(i);
                        }
                    }
                }
            }
        }
    }
    return 1;
}
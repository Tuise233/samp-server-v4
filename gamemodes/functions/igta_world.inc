


COMMAND:w(playerid,params[])
{
    if(GetPVarInt(playerid,"is_rp")) return SendClientMessage(playerid,COLOR_RED,"[T-AntiCheat]����RPģʽ��,�޷��л�С����");
    new wid[18],string[256];
    if(sscanf(params,"s[18]",wid))
    {
        SetPlayerVirtualWorld(playerid,0);
        ServerTips(playerid,"���л���������");
        return 1;
    }
    if(strval(wid))
    {
        if(!IsPlayerConnected(strval(wid))) return ServerTips(playerid,"����Ҳ�����");
        format(string,sizeof(string),"���л���IDΪ%d��С����",strval(wid));
        ServerTips(playerid,string);
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerVehicleSeat(GetPlayerVehicleID(playerid)) == 0)
            {
                new vid = GetPlayerVehicleID(playerid);
                new sid = GetPlayerVehicleSeat(playerid);
                SetVehicleVirtualWorld(vid,strval(wid));
                SetPlayerVirtualWorld(playerid,strval(wid));
                PutPlayerInVehicle(playerid,vid,sid);
                return 1;
            }
        }
        SetPlayerVirtualWorld(playerid,strval(wid));
    }
    return 1;
}

COMMAND:ww(playerid)
{
    SetPlayerVirtualWorld(playerid,playerid);
    ServerTips(playerid,"�����л����Լ���С����");
    return 1;
}

forward WorldTime();
public WorldTime()
{
    if(GetSVarInt("World_Time") == 24)
    {
        SetSVarInt("World_Time",1);
        SetWorldTime(1);
        return 1;
    }
    SetSVarInt("World_Time",GetSVarInt("World_Time")+1);
    SetWorldTime(GetSVarInt("World_Time"));  
    return 1;
}

COMMAND:pweather(playerid,params[])
{
    new wid[18];
    if(sscanf(params,"s[18]",wid)) return ServerTips(playerid,"�޸���Ҹ������� /pweather [����ID]");
    SetPlayerWeather(playerid,strval(wid));
    ServerTips(playerid,"�޸ĸ��������ɹ�");
    return 1;
}

COMMAND:ptime(playerid,params[])
{
    new hour[18];
    if(sscanf(params,"s[18]",hour)) return ServerTips(playerid,"������Ҹ���ʱ�� /ptime [ʱ��(1~24)]");
    if(strval(hour) < 1 || strval(hour) > 24) return ServerTips(playerid,"�޸ĵ�ʱ��������1~24");
    SetPlayerTime(playerid,strval(hour),0);
    ServerTips(playerid,"�޸ĸ���ʱ��ɹ�");
    return 1;
}

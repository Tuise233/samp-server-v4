// igta_vip

forward vip_OnPlayerConnect(playerid);
public vip_OnPlayerConnect(playerid)
{
    new name[64],files[64];
    GetPlayerName(playerid,name,sizeof(name));
    format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
    if(fexist(files))
    {
        SetPVarInt(playerid,"is_vip",!GetPVarInt(playerid,"is_vip"));
        new string[256];
        format(string,sizeof(string),"[VIPϵͳ]����VIP���%s(%d)������,��λ��ӭ~",name,playerid);
        SendClientMessageToAll(COLOR_VIP,string);
    }

    if(dini_Unset(files,"Ch"))
    {
        dini_IntSet(files,"Ch",0);
    }
    if(dini_Unset(files,"Xwb"))
    {
        dini_IntSet(files,"Xwb",0);
    }
    return 1;
}

forward OrderSongEx();
public OrderSongEx()
{
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        
    }
}

COMMAND:vip(playerid,params[])
{
    new params1[256],params2[256],params3[256],name[64],string[256];
    GetPlayerName(playerid,name,sizeof(name));
    if(sscanf(params,"s[256]s[256]s[256]",params1,params2,params3))
    {
        if(!strlen(params1)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]��Աϵͳʹ��˵��: /vip help");
    }

    if(!strcmp(params1,"help",true))
    {
        SendClientMessage(playerid,COLOR_VIP,"VIPϵͳ������ȫ");
        SendClientMessage(playerid,COLOR_VIP,"���ܹ����ַ:http://u6.gg/sUncz");
        SendClientMessage(playerid,COLOR_VIP,"VIP��ֵ����:/vip add");
        SendClientMessage(playerid,COLOR_RED,"Ŀǰ���ŵ�ֻ��VIP������VIP����!");
        SendClientMessage(playerid,COLOR_VIP,"VIP����:/vip tp  ||  VIP����:/vip kick  ||  ȫ�����:/vip music");
        SendClientMessage(playerid,COLOR_VIP,"�ʺ糵:/vip car  ||  VIPͷ��: /vip show");
        SendClientMessage(playerid,COLOR_VIP,"�޸ĳƺ�:/vip ch  ||  �޸�Сβ��:/vip xwb");
        SendClientMessage(playerid,COLOR_VIP,"����VIP���ܾ����ڴ�!");
        return 1;
    }

    if(!strcmp(params1,"add",true))
    {
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIP��ֵ����: /vip add [����]");
        new files[64],vfiles[64];
        //�ж��Ƿ��Ѿ���ֵ
        format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
        format(vfiles,sizeof(vfiles),"\\Server\\VIP\\%s.ini",params2);
        if(!fexist(vfiles)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]������Ŀ�������,��˶Ժ���������");
        if(!fexist(files))
        {
            dini_Create(files);
            dini_Set(files,"Name",name);
            dini_IntSet(files,"Time",dini_Int(vfiles,"Time"));
            format(string,sizeof(string),"[VIPϵͳ]��ֵ�ɹ�,��ʹ����һ��[%s]��,ʣ��ʱ��:%d��",dini_Int(vfiles,name),dini_Int(files,"Time"));
            SendClientMessage(playerid,COLOR_VIP,string);
            format(string,sizeof(string),"[VIPϵͳ]���%s(%d)VIP��ֵ�ɹ�,ʹ����һ��[%s]��,ʣ��ʱ��:%d��",name,playerid,dini_Int(vfiles,"Name"),dini_Int(files,"Time"));
            SendClientMessageToAll(COLOR_VIP,string);
            fremove(vfiles);
            SetPVarInt(playerid,"is_vip",!GetPVarInt(playerid,"is_vip"));
            return 1;
        }
        else
        {
            dini_IntSet(files,"Time",dini_Int(vfiles,"Time"));
            format(string,sizeof(string),"[VIPϵͳ]��ֵ�ɹ�,��ʹ����һ��[%s]��,ʣ��ʱ��:%d��",dini_Get(vfiles,name),dini_Int(files,"Time"));
            SendClientMessage(playerid,COLOR_VIP,string);
            format(string,sizeof(string),"[VIPϵͳ]���%s(%d)VIP��ֵ�ɹ�,ʹ����һ��[%s]��,ʣ��ʱ��:%d��",name,playerid,dini_Get(vfiles,"Name"),dini_Int(files,"Time"));
            SendClientMessageToAll(COLOR_VIP,string);
            fremove(vfiles);
            SetPVarInt(playerid,"is_vip",!GetPVarInt(playerid,"is_vip"));
            return 1;
        }
    }

    if(!GetPVarInt(playerid,"is_vip")) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]������VIP,����Ȩʹ��");
    if(!strcmp(params1,"tp",true))
    {
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIP����: /vip tp [���ID]");
        new pid = strval(params2);
        if(!IsPlayerConnected(pid)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]����Ҳ�����");
        new name1[64];
        if(GetPVarInt(pid,"is_rp")) return SendClientMessage(playerid,COLOR_RED,"[T-AntiCheat]��������ͨ��VIP���ʹ�����RP����");
        if(GetPVarInt(pid,"is_dm")) return SendClientMessage(playerid,COLOR_RED,"[T-AntiCheat]��������ͨ��VIP���ʹ�����DM����");
        GetPlayerName(pid,name1,sizeof(name1));
        format(string,sizeof(string),"[VIPϵͳ]���%s(%d)ʹ��VIP���ʹ�������ĵ�ǰ������λ��",name,playerid);
        SendClientMessage(pid,COLOR_VIP,string);
        format(string,sizeof(string),"[VIPϵͳ]��ͨ��ʹ��VIP���ʹ��������%s(%d)�ĵ�ǰ������λ��",name1,pid);
        SendClientMessage(playerid,pid,string);
        new Float:x,Float:y,Float:z;
        GetPlayerPos(pid,x,y,z);
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(pid));
        if(GetPlayerVehicleSeat(playerid) == 0)
        {
            new vid = GetPlayerVehicleID(playerid);
            SetVehiclePos(vid,x,y,z);
            SetVehicleVirtualWorld(vid, GetPlayerVirtualWorld(pid));
            PutPlayerInVehicle(playerid, vid, 0);
        }
        SetPlayerPos(playerid,x,y,z);
        return 1;
    }

    if(!strcmp(params1,"kick",true))
    {
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIP����; /vip kick [���ID] [����]");
        if(!strlen(params3)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIP����; /vip kick [���ID] [����]");
        new pid = strval(params2);
        if(!IsPlayerConnected(pid)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]����Ҳ�����");
        if(GetPVarInt(pid,"is_admin"))
        {
            format(string,sizeof(string),"[T-Admin]VIP%s(%d)�����߳�����Ա,�ѱ�ϵͳ���ز��߳�������",name,playerid);
            SendClientMessageToAll(COLOR_RED,string);
            Kick(playerid);
            return 1;   
        }
        new name1[64];
        GetPlayerName(pid,name1,sizeof(name1));
        format(string,sizeof(string),"[VIPϵͳ]���%s(%d)ʹ��VIP���˽����%s(%d)�߳�������,����:%s",name,playerid,name1,pid,params3);
        SendClientMessageToAll(COLOR_VIP,string);
        SendClientMessageToAll(COLOR_VIP,"[VIPϵͳ]����Ҷ���ʹ��VIP��������?��������ɫ����,��������ó���VIPȨ��");
        SendClientMessageToAll(COLOR_VIP,"[VIPϵͳ]�������ٱ���3��VIP");
        Kick(pid);
        format(string,sizeof(string),"IGTASMAP - VIPϵͳ\nVIP�û�:%s(%d)\n����: VIP����\n�������û�:%s(%d)\nԭ��:%s",name,playerid,name1,pid,params3);
        new files[64];
        format(files,sizeof(files),"\\Robot\\VIPSystem.txt");
        new File:fl = fopen(files,io_write);
        for(new i=0;string[i];i++)
        {
            fputchar(fl,string[i],false);
        }
        fclose(fl);
        return 1;
    }

    if(!strcmp(params1,"music",true))
    {
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIPȫ�����: /vip music [��������]");
        format(string,sizeof(string),"[VIPϵͳ]���%s(%d)ʹ��VIP���Ϊȫ����ҵ���һ�׸�",name,playerid);
        SendClientMessageToAll(COLOR_VIP,string);
        SendClientMessageToAll(COLOR_VIP,"[VIPϵͳ]��ǰ���������������,����/stopmusic���ر�����");
        for(new i=0;i<MAX_PLAYERS;i++)
        {
            if(IsPlayerConnected(i))
            {
                PlayAudioStreamForPlayer(i, params2);
            }
        }
        return 1;
    }

    if(!strcmp(params1,"car",true))
    {
        if(!GetPVarInt(playerid,"is_vip_car"))
        {
            SetPVarInt(playerid,"is_vip_car",1);
            SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]���ѿ����ʺ糵,�����ؾ߻����������ɫ");
            SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]�ֻ������ʱ�޷���ʾ�ؾߵ���ɫ����");
        }
        else
        {
            DeletePVar(playerid,"is_vip_car");
            SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]���ѹرղʺ糵");
        }
        return 1;
    }

    if(!strcmp(params1,"show",true))
    {
        if(!GetPVarInt(playerid,"is_vip_show"))
        {
            SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]VIPͷ��չʾ���°�IGTASAMP�ſ���ʹ��");
        }
        return 1;
    }

    if(!strcmp(params1,"clear",true))
    {
        for(new i=0;i<15;i++)
        {
            SendClientMessageToAll(COLOR_VIP," ");
        }
        format(string,sizeof(string),"[VIPϵͳ]���%s(%d)ʹ��VIP��������˹����Ի�",name,playerid);
        SendClientMessageToAll(COLOR_VIP,string);
    }

    if(!strcmp(params1,"ch",true))
    {
        new files[64];
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]�Զ���ƺ�: /vip ch [�ƺ�] (��Ϊ���ɻ�������޸Ļ���)");
        format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
        if(dini_Int(files,"Ch") == 2) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]����ʹ���������޸ĳƺŵĻ���");
        format(files,sizeof(files),"\\Players\\%s.ini",name);
        dini_Set(files,"Ch",params2);
        format(string,sizeof(string),"[VIPϵͳ]VIP%s(%d)�޸����Լ��ĳƺ�: %s",name,playerid,params2);
        SendClientMessageToAll(COLOR_VIP,string);
        format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
        dini_IntSet(files,"Ch",dini_Int(files,"Ch") + 1);
    }

    if(!strcmp(params1,"xwb",true))
    {
        new files[64];
        if(!strlen(params2)) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]�Զ���ƺ�: /vip xwb [Сβ��] (��Ϊ���ɻ�������޸Ļ���)");
        format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
        if(dini_Int(files,"Xwb") == 2) return SendClientMessage(playerid,COLOR_VIP,"[VIPϵͳ]����ʹ���������޸�Сβ�͵Ļ���");
        format(files,sizeof(files),"\\Players\\%s.ini",name);
        dini_Set(files,"Xwb",params2);
        format(string,sizeof(string),"[VIPϵͳ]VIP%s(%d)�޸����Լ���Сβ��: %s",name,playerid,params2);
        SendClientMessageToAll(COLOR_VIP,string);
        format(files,sizeof(files),"\\Server\\VIP\\Members\\%s.ini",name);
        dini_IntSet(files,"Xwb",dini_Int(files,"Xwb") + 1);
    }
    return 1;
}

forward RGBCar();
public RGBCar()
{
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(GetPVarInt(i,"is_vip_car"))
        {
            if(GetPlayerVehicleSeat(i) == 0)
            {
                if(!GetPVarInt(i,"is_rp"))
                {
                    ChangeVehicleColor(GetPlayerVehicleID(i), random(20), random(20));
                }
            }
        }
    }
    return 1;
}
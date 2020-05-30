COMMAND:skin(playerid,params[])
{
    new skinid[18],files[64],name[64];
    GetPlayerName(playerid,name,sizeof(name));
    if(sscanf(params,"s[18]",skinid)) return ServerTips(playerid,"�޸�Ƥ�� /skin [Ƥ��ID]");
    if(strval(skinid) < 0|| strval(skinid) >299) return ServerTips(playerid,"Ƥ��ID������0~299��");
    format(files,sizeof(files),"\\Players\\%s.ini",name);
    dini_IntSet(files,"Skin",strval(skinid));
    SetPlayerSkin(playerid,strval(skinid));
    ServerTips(playerid,"���ѳɹ��޸�Ƥ��");
    return 1;
}

COMMAND:pm(playerid,params[])
{
    new pid[18],name[64],name1[64],string[256],content[256];
    new year,month,day,hour,mini,sec;
    new time[64];
    if(GetPVarInt(playerid,"is_cpm")) return ServerTips(playerid,"���ѹر�˽��ϵͳ,�޷�����˽��,����/cpm���ɿ���˽��ϵͳ");
    getdate(year,month,day);
    gettime(hour,mini,sec);
    format(time,sizeof(time),"[%d/%d/%d %d:%d:%d]",year,month,day,hour,mini,sec);
    if(sscanf(params,"s[64]s[256]",pid,content)) return ServerTips(playerid,"˽����� /skin [���ID] [����]"); 
    if(!IsPlayerConnected(strval(pid))) return ServerTips(playerid,"����Ҳ�����");
    if(GetPVarInt(strval(pid),"is_cpm")) return ServerTips(playerid,"������ѹر�˽��ϵͳ,���޷���������˽��");
    if(GetPVarInt(playerid,"is_rp") || GetPVarInt(strval(pid),"is_rp")) return ServerTips(playerid,"RPģʽ���޷�ʹ��˽��ϵͳ");
    if(!GetPVarInt(strval(pid),"is_admin"))
    {
        if(GetPVarInt(playerid,"is_mute")) return AdminTips(playerid,"���ѱ�����,�޷�ʹ��˽��ϵͳ");
    }
    GetPlayerName(playerid,name,sizeof(name));
    GetPlayerName(strval(pid),name1,sizeof(name1));
    format(string,sizeof(string),"%s%s(%d):%s_Private to %s(%d)\n",time,name,playerid,content,name1,strval(pid));
    WriteChatLog(string);
    format(string,sizeof(string),"���%s(%d)˽�Ķ���˵:%s",name,playerid,content);
    ServerTips(strval(pid),string);
    AdminTips(strval(pid),"����/cpm�ɹر�PMϵͳ");
    format(string,sizeof(string),"��˽�Ķ����%s(%d)˵:%s",name1,strval(pid),content);
    ServerTips(playerid,string);
    format(string,sizeof(string),"���%s(%d)˽�Ķ����%s(%d)˵:%s",name,playerid,name1,strval(pid),content);
    for(new i=0;i<MAX_PLAYERS;i++)
    {
        if(GetPVarInt(i,"is_admin"))
        {
            ServerTips(i,string);
        }
    }
    return 1;
}

COMMAND:cpm(playerid)
{
    if(!GetPVarInt(playerid,"is_cpm"))
    {
        SetPVarInt(playerid,"is_cpm",!GetPVarInt(playerid,"is_cpm"));
        ServerTips(playerid,"���ѹر�˽��ϵͳ,��������/cpm�������¿���");
    }
    else
    {
        DeletePVar(playerid,"is_cpm");
        ServerTips(playerid,"���Ѿ�����˽��ϵͳ,��������/cpm�������¹ر�");
    }
    return 1;
}

COMMAND:ctp(playerid)
{
    if(!GetPVarInt(playerid,"is_ctp"))
    {
        SetPVarInt(playerid,"is_ctp",!GetPVarInt(playerid,"is_ctp"));
        ServerTips(playerid,"�ѿ�������CTPȨ��");
        return 1;
    }
    DeletePVar(playerid,"is_ctp");
    ServerTips(playerid,"�ѹر�����CTPȨ��");
    return 1;
}

COMMAND:tp(playerid,params[])
{
    new name[64],name1[64],string[256],pid[18];
    new Float:x,Float:y,Float:z;
    if(sscanf(params,"s[18]",pid)) return ServerTips(playerid,"���͵���Ҹ���: /tp [���ID]");
    if(!GetPVarInt(playerid,"is_ctp")) return ServerTips(playerid,"��δ����CTPȨ��");
    if(!IsPlayerConnected(strval(pid))) return ServerTips(playerid,"����Ҳ�����");
    if(!GetPVarInt(strval(pid),"is_ctp")) return ServerTips(playerid,"�����δ����CTPȨ��");
    GetPlayerPos(strval(pid),x,y,z);
    SetPlayerPos(playerid,x,y,z);
    GetPlayerName(playerid,name,sizeof(name));
    GetPlayerName(strval(pid),name1,sizeof(name1));
    format(string,sizeof(string),"���%s(%d)�������������",name,playerid);
    ServerTips(strval(pid),string);
    format(string,sizeof(string),"�㴫�������%s(%d)������",name1,strval(pid));
    ServerTips(playerid,string);
    return 1;
}

COMMAND:tv(playerid,params[])
{
    new params1[18],name[64],string[256];
    if(sscanf(params,"s[18]",params1)) return ServerTips(playerid,"�۲칦��ʹ��ָ�� /tv help");

    if(strval(params1))
    {
        if(!IsPlayerConnected(strval(params1))) return ServerTips(playerid,"����Ҳ�����");
        GetPlayerName(strval(params),name,sizeof(name));
        format(string,sizeof(string),"���ѿ�ʼ�۲����%s(%d)",name,strval(params1));
        ServerTips(playerid,string);
        TogglePlayerSpectating(playerid, 1);
        SetPVarInt(playerid,"is_tv",strval(params1)+1);
        SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(strval(params1)));
        if(IsPlayerInAnyVehicle(strval(params1)))
        {
            PlayerSpectateVehicle(playerid, GetPlayerVehicleID(strval(params1)));
            return 1;
        }
        PlayerSpectatePlayer(playerid, strval(params1),SPECTATE_MODE_NORMAL);
        return 1;
    }

    if(!strcmp(params1,"leave",true))
    {
        DeletePVar(playerid,"is_tv");
        SetPlayerVirtualWorld(playerid,0);
        TogglePlayerSpectating(playerid,0);
        ServerTips(playerid,"�����˳��۲�");
        return 1;
    }

    if(!strcmp(params1,"help",true))
    {
        ServerTips(playerid,"�۲칦��ʹ��ָ��");
        ServerTips(playerid,"�۲���� /tv [���ID] || �˳��۲� /tv leave");
        return 1;
    }
    return 1;
}

forward AutoMessage();
public AutoMessage()
{
    new files[64],string[1024],num[18];
    new a=0;
    format(files,sizeof(files),"\\Server\\AutoMessage.ini");
    for(new i=0;i<50;i++)
    {
        format(num,sizeof(num),"Msg[%d]",i);
        if(dini_Isset(files,num))
        {
            a = a+1;
        }
    }
    format(num,sizeof(num),"Msg[%d]",random(a));
    format(string,sizeof(string),"[����������]%s",dini_Get(files,num));
    SendClientMessageToAll(COLOR_GREEN,string);
    return 1;
}

COMMAND:kill(playerid)
{
    SetPlayerHealth(playerid, 0);
    ServerTips(playerid,"��ѡ������ɱ...");
    return 1;   
}

COMMAND:skick(playerid,params[])
{
    if(!GetPVarInt(playerid,"is_login")) return ServerTips(playerid,"����û�е�¼,�޷������κβ���");
    new pid[18],reason[64],name[64],name1[64],string[256];
    if(sscanf(params,"s[18]s[64]",pid,reason)) return ServerTips(playerid,"ͶƱ���� /skick [���ID] [ԭ��]");
    for(new i=0;i<MAX_PLAYERS;i++){
        if(GetPVarInt(i,"is_skick_count")){
            ServerTips(playerid,"Ŀǰ����һ��ͶƱ�������ڽ���,���Ժ�����");
            return 1;
        }
    }
    if(!IsPlayerConnected(strval(pid))) return ServerTips(playerid,"����Ҳ�����");
    GetPlayerName(playerid,name,sizeof(name));
    GetPlayerName(strval(pid),name1,sizeof(name1));
    if(GetPVarInt(strval(pid),"is_admin"))
    {
        format(string,sizeof(string),"[ͶƱ����]���%s(%d)�����߳�����Ա%s(%d),�ѱ�ϵͳ�߳�������",name,playerid,name1,strval(pid));
        CheatTips(-1,string);
        Kick(playerid);
        return 1;
    }
    format(string,sizeof(string),"[ͶƱ����]���%s(%d)�����߳����%s(%d),ԭ��:%s",name,playerid,name1,strval(pid),reason);
    SendClientMessageToAll(COLOR_RED,string);
    SendClientMessageToAll(COLOR_RED,"[ͶƱ����]���� /ty ͬ���߳������,���� /bty ��ͬ���߳������");
    SetPVarInt(playerid,"is_skick",123);
    SetPVarInt(strval(pid),"is_skick",!GetPVarInt(playerid,"is_skick"));
    SetPVarInt(strval(pid),"is_skick_count",30);
    SetPVarInt(strval(pid),"is_skick_ty",1);
    SetPVarInt(strval(pid),"is_skick_bty",1);
    return 1;
}

COMMAND:ty(playerid)
{
    if(!GetPVarInt(playerid,"is_login")) return ServerTips(playerid,"����û�е�¼,�޷������κβ���");
    new a = 0,pid = 0;
    new name[64],name1[64],string[256];
    if(GetPVarInt(playerid,"is_skick")) return ServerTips(playerid,"���Ѿ������ͶƱ,�޷��ٴ�ͶƱ");
    for(new i=0;i<MAX_PLAYERS;i++){
        if(GetPVarInt(i,"is_skick_count")){
            a = a + 1;
            pid = i;
        }
    }
    if(a == 0) return ServerTips(playerid,"��ǰû��������ڽ���ͶƱ����");
    else{
        GetPlayerName(playerid,name,sizeof(name));
        GetPlayerName(pid,name1,sizeof(name1));
        format(string,sizeof(string),"[ͶƱ����]���%s(%d)ͬ���߳�%s(%d)",name,playerid,name1,pid);
        SendClientMessageToAll(COLOR_RED,string);
        SetPVarInt(playerid,"is_skick",!GetPVarInt(playerid,"is_skick"));
        SetPVarInt(pid,"is_skick_ty",GetPVarInt(pid,"is_skick_ty")+1);
        return 1;
    }
}

COMMAND:bty(playerid)
{
    if(!GetPVarInt(playerid,"is_login")) return ServerTips(playerid,"����û�е�¼,�޷������κβ���");
    new a = 0,pid = 0;
    new name[64],name1[64],string[256];
    if(GetPVarInt(playerid,"is_skick")) return ServerTips(playerid,"���Ѿ������ͶƱ,�޷��ٴ�ͶƱ");
    for(new i=0;i<MAX_PLAYERS;i++){
        if(GetPVarInt(i,"is_skick_count")){
            a = a + 1;
            pid = i;
        }
    }
    if(a == 0) return ServerTips(playerid,"��ǰû��������ڽ���ͶƱ����");
    else{
        GetPlayerName(playerid,name,sizeof(name));
        GetPlayerName(pid,name1,sizeof(name1));
        format(string,sizeof(string),"[ͶƱ����]���%s(%d)��ͬ���߳�%s(%d)",name,playerid,name1,pid);
        SendClientMessageToAll(COLOR_RED,string);
        SetPVarInt(playerid,"is_skick",!GetPVarInt(playerid,"is_skick"));
        SetPVarInt(pid,"is_skick_bty",GetPVarInt(pid,"is_skick_bty")+1);
        return 1;
    }
}

forward SkickCheck();
public SkickCheck()
{
    new string[256],name[64];
    for(new i=0;i<MAX_PLAYERS;i++){
        if(GetPVarInt(i,"is_skick_count")){
            if(GetPVarInt(i,"is_skick_count") == 1){
                if(GetPVarInt(i,"is_skick_ty") > GetPVarInt(i,"is_skick_bty")){
                    GetPlayerName(i,name,sizeof(name));
                    format(string,sizeof(string),"[ͶƱ����]���%s(%d)���߳�������,ͶƱ��� - ͬ��%dƱ || ��ͬ��%dƱ",name,i,GetPVarInt(i,"is_skick_ty"),GetPVarInt(i,"is_skick_bty"));
                    SendClientMessageToAll(COLOR_RED,string);
                    Kick(i);
                    for(new a=0;a<MAX_PLAYERS;a++){
                        if(GetPVarInt(a,"is_skick") || GetPVarInt(a,"is_skick_count") || GetPVarInt(i,"is_skick_ty") || GetPVarInt(i,"is_skick_bty")){
                            DeletePVar(a,"is_skick");
                            DeletePVar(a,"is_skick_count");
                            DeletePVar(a,"is_skick_ty");
                            DeletePVar(a,"is_skick_bty");
                        }
                    }
                    return 1;
                }
                if(GetPVarInt(i,"is_skick_ty") <= GetPVarInt(i,"is_skick_bty")){
                    GetPlayerName(i,name,sizeof(name));
                    format(string,sizeof(string),"[ͶƱ����]���%s(%d)δ���߳�������,ͶƱ��� - ͬ��%dƱ || ��ͬ��%dƱ",name,i,GetPVarInt(i,"is_skick_ty"),GetPVarInt(i,"is_skick_bty"));
                    SendClientMessageToAll(COLOR_RED,string);
                    for(new a=0;a<MAX_PLAYERS;a++){
                    if(GetPVarInt(a,"is_skick") || GetPVarInt(a,"is_skick_count") || GetPVarInt(i,"is_skick_ty") || GetPVarInt(i,"is_skick_bty")){
                            DeletePVar(a,"is_skick");
                            DeletePVar(a,"is_skick_count");
                            DeletePVar(a,"is_skick_ty");
                            DeletePVar(a,"is_skick_bty");
                        }
                    }
                }
                return 1;
            }
            else{
                SetPVarInt(i,"is_skick_count",GetPVarInt(i,"is_skick_count") - 1);
            }
        }
    }
    return 1;
}

COMMAND:mtp(playerid)
{
    if(GetPVarInt(playerid,"is_mtp")){
        DeletePVar(playerid,"is_mtp");
        ServerTips(playerid,"�ѹرյ�ͼ���͹���");
        return 1;
    }
    SetPVarInt(playerid,"is_mtp",!GetPVarInt(playerid,"is_mtp"));
    ServerTips(playerid,"�ѿ�����ͼ���͹���");
    return 1;
}

COMMAND:wudi(playerid)
{
    if(GetPVarInt(playerid,"is_rp")) return RpTips(playerid,"������RPģʽ��,�޷������޵�");
    if(GetPVarInt(playerid,"is_god")){
        DeletePVar(playerid,"is_god");
        ServerTips(playerid,"���ѹر��޵�ģʽ");
        SetPlayerHealth(playerid,100);
        SetPlayerArmour(playerid,100);
        return 1;
    }
    SetPVarInt(playerid,"is_god",99);
    ServerTips(playerid,"���ѿ����޵�ģʽ");
    return 1;
}

forward God();
public God()
{
    for(new i=0;i<MAX_PLAYERS;i++){
        if(GetPVarInt(i,"is_god")){
            SetPlayerHealth(i,10000);
            SetPlayerArmour(i,10000);
        }
    }
    return 1;
}

COMMAND:qian(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x+3,y,z);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:hou(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x-3,y,z);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:zuo(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x,y+3,z);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:you(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x,y-3,z);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:shang(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x,y,z+3);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:xia(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerPos(playerid,x,y,z-3);
    ServerTips(playerid,"�ѵ�������λ��");
    return 1;
}

COMMAND:point(playerid)
{
    new Float:x,Float:y,Float:z;
    GetPlayerPos(playerid,x,y,z);
    SetPlayerCheckpoint(playerid,x,y,z,20.0);
    return 1;
}

forward Afking();
public Afking()
{
    //128.362945,-1931.474975,-0.354136
    //185.009384,-1970.584350,-0.616092
    new Float:x,Float:y,Float:z;
    for(new i=0;i<MAX_PLAYERS;i++){
        GetPlayerPos(i,x,y,z);
        if(x > 128.362945 && x < 185.009384 && y < -1931.474975 && y > -1970.584350){
            if(!GetPVarInt(i,"is_afking")){
                SetPVarInt(i,"is_afking",!GetPVarInt(i,"is_afking"));
                ServerTips(i,"�������ڷ������һ���,�������˫����ʱ���");
            }
        }
        else{
            if(GetPVarInt(i,"is_afking")){
                DeletePVar(i,"is_afking");
                ServerTips(i,"�����뿪�������һ���,����������˫����ʱ���");
            }
        }
    }
    return 1;
}

COMMAND:logs(playerid)
{
    new num[64],files[64],string[256];
    format(files,sizeof(files),"\\Server\\AutoMessage.ini");
    for(new i=0;i<99;i++){
        format(num,sizeof(num),"Log[%d]",i);
        if(dini_Isset(files,num)){
            format(string,sizeof(string),"%s",dini_Get(files,num));
            ServerTips(playerid,string);
        }
    }
    return 1;
}

COMMAND:qd(playerid)
{
    new name[64],files[64],string[256];
    GetPlayerName(playerid,name,sizeof(name));
    format(files,sizeof(files),"\\Players\\%s.ini",name);
    new year,month,day;
    getdate(year,month,day);
    if(dini_Int(files,"Sign") == day){
        ServerTips(playerid,"�������Ѿ�ǩ����,�޷�����ǩ��");
        return 1;
    }
    dini_IntSet(files,"Sign",day);
    format(string,sizeof(string),"���%s(%d)������ǩ��,����10ʱ���",name,playerid);
    ServerTips(-1,string);
    SetPlayerScore(playerid,GetPlayerScore(playerid)+10);
    return 1;
}

COMMAND:stopmusic(playerid)
{
    StopAudioStreamForPlayer(playerid);
    SendClientMessage(playerid,COLOR_GREEN,"[ϵͳ]��Ϊ���ر�����");
    return 1;
}

stock GetName(playerid)
{
    new name[64];
    GetPlayerName(playerid,name,sizeof(name));
    return name;
}
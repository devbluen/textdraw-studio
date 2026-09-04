
enum E_TYPECAMERA {
    E_TYPECAMERA_PLAYER,
    E_TYPECAMERA_ROAD,
    E_TYPECAMERA_GROOVE,
    E_TYPECAMERA_SANTA_MONICA,
    E_TYPECAMERA_BUILDING,
    E_TYPECAMERA_BEACH,
};

static enum E_DATAINFO {
    E_TYPECAMERA:E_DATAINFO_TYPE,
    E_DATAINFO_NAME[30 + 1],
    Float:E_DATAINFO_POSITION[4]
};

static const
    e_DataInfo[][E_DATAINFO] = {
        {E_TYPECAMERA_PLAYER,           "Player",               {1923.5066, -2547.8245, 14.0469, 90.0}},
        {E_TYPECAMERA_ROAD,             "Road",                 {1714.6931,-1340.4772,13.3828,180.1136}},
        {E_TYPECAMERA_GROOVE,           "Grove",                {2450.7434,-1658.5571,13.3047,258.7504}},
        {E_TYPECAMERA_SANTA_MONICA,     "Santa Monica Pier",    {370.1010,-2032.7593,7.6719,0.7464}},
        {E_TYPECAMERA_BUILDING,         "Building",             {1547.9363,-1352.2819,329.4693,15.2985}},
        {E_TYPECAMERA_BEACH,            "Beach",                {482.6832,-1857.9556,3.6218,248.6140}}
    }
;

static E_TYPECAMERA:eType[MAX_PLAYERS];



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

static stock GetIndexInternal_Type(E_TYPECAMERA:type) {

    static
        E_TYPECAMERA:oldType = E_TYPECAMERA:-1,
        oldIndex = -1
    ;

    if(oldType != E_TYPECAMERA:-1 && oldType == type)
        return oldIndex;

    oldIndex = -1;
    oldType = type;

    for(new i = 0; i < sizeof e_DataInfo; i++) {
        if(e_DataInfo[i][E_DATAINFO_TYPE] != type)
            continue;

        oldIndex = i;
        break;
    }
    return oldIndex;
}

stock Camera_GetName(E_TYPECAMERA:type, dest[], maxLength = sizeof dest) {
    new index = GetIndexInternal_Type(type);
    strcat(dest, e_DataInfo[index][E_DATAINFO_NAME], maxLength);
}

stock Camera_Get(E_TYPECAMERA:type, &Float:x, &Float:y, &Float:z, &Float:angle) {

    new index = GetIndexInternal_Type(type);

    x = e_DataInfo[index][E_DATAINFO_POSITION][0];
    y = e_DataInfo[index][E_DATAINFO_POSITION][1];
    z = e_DataInfo[index][E_DATAINFO_POSITION][2];
    angle = e_DataInfo[index][E_DATAINFO_POSITION][3];
}

stock Camera_GetNameByPlayer(playerid, dest[], maxLength = sizeof dest) {
    new E_LANG:camKey = E_LANG_CAM_PLAYER;
    camKey = E_LANG:(_:camKey + _:eType[playerid]);
    strcat(dest, L(playerid, camKey), maxLength);
}

stock Camera_Set(playerid, E_TYPECAMERA:type) {

    new Float:position[4];
    Camera_Get(type, position[0], position[1], position[2], position[3]);

    SetPlayerPos(playerid, position[0], position[1], position[2]);
    SetPlayerFacingAngle(playerid, position[3]);

    eType[playerid] = type;

    if(type == E_TYPECAMERA_PLAYER) SetCameraBehindPlayer(playerid);
    else
    {
        Util_GetForwardAngle(position[0], position[1], position[3], 2.0);
        SetPlayerCameraPos(playerid, position[0], position[1], position[2] + 4.0);

        Util_GetForwardAngle(position[0], position[1], position[3], 8.0);
        SetPlayerCameraLookAt(playerid, position[0], position[1], position[2], CAMERA_CUT);
    }
}

stock Camera_Show(playerid) {
    
    inline CameraOptionsData() {

        for(new i = 0; i < sizeof e_DataInfo; i++) {
            new E_LANG:camKey = E_LANG_CAM_PLAYER;
            camKey = E_LANG:(_:camKey + i);
            DialogMod_Add(playerid, L(playerid, camKey), i);
        }

    }

    DialogMod_Create(playerid, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_CAMERAS), L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL), "D_CAMERA_MODE", using inline CameraOptionsData);
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  
                                                                                                            
                                                    .o8                                                   
                                                    "888                                                   
                    ooo. .oo.  .oo.    .ooooo.   .oooo888                                                   
                    `888P"Y88bP"Y88b  d88' `88b d88' `888                                                   
                    888   888   888  888   888 888   888                                                   
                    888   888   888  888   888 888   888                                                   
                    o888o o888o o888o `Y8bod8P' `Y8bod88P"                                                  

*/

DialogMod:D_CAMERA_MODE(playerid, response, inputtext[], index) {

    if(response) 
        Camera_Set(playerid, e_DataInfo[index][E_DATAINFO_TYPE]);
    
    return true;
}
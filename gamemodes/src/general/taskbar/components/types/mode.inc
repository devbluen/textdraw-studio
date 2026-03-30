
enum E_TYPEMODE {
    E_TYPEMODE_PLAYER = 0,
    E_TYPEMODE_GLOBAL = 1
};

static enum E_DATAINFO {
    E_TYPEMODE:E_DATAINFO_TYPE,
    E_DATAINFO_SPRITE[20 + 1],
    E_DATAINFO_NAME[20 + 1]
};

static const 
    e_DataInfo[][E_DATAINFO] = {
        {E_TYPEMODE_PLAYER, "player", "Player"},
        {E_TYPEMODE_GLOBAL, "global", "Global"}
    }
;



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

static stock GetIndexInternal_Type(E_TYPEMODE:type) {

    static
        E_TYPEMODE:oldType = E_TYPEMODE:-1,
        oldIndex = -1
    ;

    if(oldType != E_TYPEMODE:-1 && oldType == type)
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

stock TaskBarTypeMode_GetSprite(E_TYPEMODE:type) {
    new 
        string[20 + 1],
        index = GetIndexInternal_Type(type)
    ;

    strcat(string, e_DataInfo[index][E_DATAINFO_SPRITE]);
    return string;
}

stock TaskBarTypeMode_GetName(E_TYPEMODE:type) {
    new 
        string[20 + 1],
        index = GetIndexInternal_Type(type)
    ;

    strcat(string, e_DataInfo[index][E_DATAINFO_NAME]);
    return string;
}

// if need TEXT_DRAW_FONT
enum E_TYPEFONT {
    E_TYPEFONT_0 = 0,
    E_TYPEFONT_1 = 1,
    E_TYPEFONT_2 = 2,
    E_TYPEFONT_3 = 3,
    E_TYPEFONT_SPRITE = 4,
    E_TYPEFONT_MODEL = 5
};

static enum E_DATAINFO {
    E_TYPEFONT:E_DATAINFO_TYPE,
    E_DATAINFO_SPRITE[20 + 1],
    E_DATAINFO_NAME[45 + 1]
};

static const 
    e_DataInfo[][E_DATAINFO] = {
        {E_TYPEFONT_0, "font1", "TEXT_DRAW_FONT_0"},
        {E_TYPEFONT_1, "font2", "TEXT_DRAW_FONT_1"},
        {E_TYPEFONT_2, "font3", "TEXT_DRAW_FONT_2"},
        {E_TYPEFONT_3, "font4", "TEXT_DRAW_FONT_3"},
        {E_TYPEFONT_SPRITE, "fontSprite", "TEXT_DRAW_FONT_SPRITE_DRAW"},
        {E_TYPEFONT_MODEL, "fontModel", "TEXT_DRAW_FONT_MODEL_PREVIEW"}
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

static stock GetIndexInternal_Type(E_TYPEFONT:type) {

    static
        E_TYPEFONT:oldType = E_TYPEFONT:-1,
        oldIndex = -1
    ;

    if(oldType != E_TYPEFONT:-1 && oldType == type)
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

stock TaskBarTypeFont_GetSprite(E_TYPEFONT:type) {
    new 
        string[20 + 1],
        index = GetIndexInternal_Type(type)
    ;

    strcat(string, e_DataInfo[index][E_DATAINFO_SPRITE]);
    return string;
}

stock TaskBarTypeFont_GetName(type) {
    new 
        string[45 + 1],
        index = GetIndexInternal_Type(E_TYPEFONT:type)
    ;

    strcat(string, e_DataInfo[index][E_DATAINFO_NAME]);
    return string;
}

stock E_TYPEFONT:TaskBarTypeFont_GetType(const string[]) {

    for(new i = 0; i < sizeof e_DataInfo; i++)
        if(isequal(e_DataInfo[i][E_DATAINFO_NAME], string, true))
            return e_DataInfo[i][E_DATAINFO_TYPE];

    return E_TYPEFONT_0;
}
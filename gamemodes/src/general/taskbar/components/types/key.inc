
enum E_TYPEKEY {
    E_TYPEKEY_DISABLED,
    E_TYPEKEY_POSITION,
    E_TYPEKEY_SIZE,
    E_TYPEKEY_LETTER_SIZE,
    E_TYPEKEY_COLOR,
    E_TYPEKEY_COLOR_BACKGROUND,
    E_TYPEKEY_COLOR_BOX,
    E_TYPEKEY_MODEL_ROTATION,
    E_TYPEKEY_GROUP_POSITION,
    E_TYPEKEY_GROUP_SIZE,
    E_TYPEKEY_GROUP_LETTER_SIZE,
    E_TYPEKEY_TASKBAR,
    E_TYPEKEY_GROUP_LOCAL_POSITION,
    E_TYPEKEY_GROUP_LOCAL_SIZE,
    E_TYPEKEY_GROUP_LOCAL_LETTER_SIZE,
    E_TYPEKEY_MOVE_INDEX,
    E_TYPEKEY_SELECT_INDEX
};

static enum E_DATAINFO {
    E_TYPEKEY:E_DATAINFO_KEY,
    E_TYPETASKBUTTON:E_DATAINFO_BUTTON
};

static const
    e_DataInfo[][E_DATAINFO] = {
        {E_TYPEKEY_POSITION,            E_TYPETASKBUTTON_POSITION},
        {E_TYPEKEY_SIZE,                E_TYPETASKBUTTON_SIZE},
        {E_TYPEKEY_LETTER_SIZE,         E_TYPETASKBUTTON_LETTERSIZE},
        {E_TYPEKEY_COLOR,               E_TYPETASKBUTTON_COLOR},
        {E_TYPEKEY_COLOR_BACKGROUND,    E_TYPETASKBUTTON_COLOR_BG},
        {E_TYPEKEY_COLOR_BOX,           E_TYPETASKBUTTON_COLOR_BOX},
        {E_TYPEKEY_MODEL_ROTATION,      E_TYPETASKBUTTON_MODELS}
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

static stock GetIndexInternal_TypeKey(E_TYPEKEY:type) {
    
    static
        E_TYPEKEY:oldType = E_TYPEKEY:-1,
        oldIndex = -1
    ;

    if(oldType != E_TYPEKEY:-1 && oldType == type)
        return oldIndex;

    oldIndex = -1;
    oldType = type;

    for(new i = 0; i < sizeof e_DataInfo; i++) {
        if(e_DataInfo[i][E_DATAINFO_KEY] != type)
            continue;

        oldIndex = i;
        break;
    }
    return oldIndex;
}

static stock GetIndexInternal_TypeButton(E_TYPETASKBUTTON:type) {
    
    static
        E_TYPETASKBUTTON:oldType = E_TYPETASKBUTTON:-1,
        oldIndex = -1
    ;

    if(oldType != E_TYPETASKBUTTON:-1 && oldType == type)
        return oldIndex;

    oldIndex = -1;
    oldType = type;

    for(new i = 0; i < sizeof e_DataInfo; i++) {
        if(e_DataInfo[i][E_DATAINFO_BUTTON] != type)
            continue;

        oldIndex = i;
        break;
    }
    return oldIndex;
}

stock E_TYPEKEY:TaskBarTypeKey_GetKey(E_TYPETASKBUTTON:button) {
    new index = GetIndexInternal_TypeButton(button);
    return index == -1 ? (E_TYPEKEY:-1) : e_DataInfo[index][E_DATAINFO_KEY]; 
}

stock E_TYPETASKBUTTON:TaskBarTypeKey_GetButton(E_TYPEKEY:key) {
    new index = GetIndexInternal_TypeKey(key);
    return index == -1 ? (E_TYPETASKBUTTON:-1) : e_DataInfo[index][E_DATAINFO_BUTTON]; 
}
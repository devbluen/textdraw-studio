
            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_TYPEKEY:E_DATA_TYPE
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogout(playerid) {

    TaskBarKey_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarKey_Set(playerid, E_TYPEKEY:type) {

    if(TaskBarKey_GetType(playerid) == type) 
        return;

    if(TaskBarKey_GetType(playerid) != E_TYPEKEY_DISABLED)
        TaskBarEventMoviment_Close(playerid);
    
    e_Data[playerid][E_DATA_TYPE] = type;

    TaskBar_Cursor(playerid, type == E_TYPEKEY_DISABLED);
    TogglePlayerControllable(playerid, type == E_TYPEKEY_DISABLED);

    if(type == E_TYPEKEY_DISABLED) 
        TaskBarEventMoviment_Unload(playerid);
    else 
        TaskBarEventMoviment_Init(playerid);
}

stock E_TYPEKEY:TaskBarKey_GetType(playerid)
    return e_Data[playerid][E_DATA_TYPE];

stock bool:TaskBarKey_Enabled(playerid)
    return TaskBarKey_GetType(playerid) != E_TYPEKEY_DISABLED;

static stock TaskBarKey_Reset(playerid) {

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
}
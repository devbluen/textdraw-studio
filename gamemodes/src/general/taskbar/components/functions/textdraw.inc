
            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    bool:E_DATA_SELECT,
    E_DATA_SELECTED_ID
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogin(playerid) {
    
    TaskBarTextdraw_SetSelected(playerid, -1);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnUserLogout(playerid) {

    TaskBarTextdraw_Reset(playerid);
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

stock TaskBarTextdraw_Select(playerid, index) {

    TaskBarTextdraw_SetSelected(playerid, index);
    CallLocalFunction("OnPlayerTaskBarDrawSelected", "ii", playerid, index);
}

stock TaskBarTextdraw_UnSelect(playerid) {

    Dialog_Hide(playerid);
    TaskBarTextdraw_SetSelected(playerid, -1);
    CallLocalFunction("OnPlayerTaskBarDrawUnSelected", "i", playerid);
}

stock TaskBarTextdraw_SetSelected(playerid, index) {

    if(e_Data[playerid][E_DATA_SELECTED_ID] == index)
        return;

    if(TaskBarTextdraw_Selected(playerid)) {
        new oldIndex = TaskBarTextdraw_GetSelected(playerid);
        SessionTextdraw_RemoveSelect(playerid, oldIndex);
    }

    if(index != -1) SessionTextdraw_SetSelect(playerid, index);

    e_Data[playerid][E_DATA_SELECT] = index != -1;
    e_Data[playerid][E_DATA_SELECTED_ID] = index;
}

stock bool:TaskBarTextdraw_Selected(playerid)
    return e_Data[playerid][E_DATA_SELECT];

stock TaskBarTextdraw_GetSelected(playerid)
    return TaskBarTextdraw_Selected(playerid) ? e_Data[playerid][E_DATA_SELECTED_ID] : -1;

static stock TaskBarTextdraw_Reset(playerid) {

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
}
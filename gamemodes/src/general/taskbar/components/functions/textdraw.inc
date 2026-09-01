
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnTaskBar_RestoreColor(playerid, index);

static enum E_DATA {
    bool:E_DATA_SELECT,
    E_DATA_SELECTED_ID,
    
    // Feedback Visual
    E_DATA_COLOR_INDEX,
    E_DATA_COLOR_TIMER
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogin(playerid) {
    
    TaskBarTextDraw_SetSelected(playerid, -1);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnUserLogout(playerid) {

    TaskBarTextDraw_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnTaskBar_RestoreColor(playerid, index)
    TaskBarTextDraw_RestoreColor(playerid, index);



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarTextDraw_Select(playerid, index, bool:effect = true) {

    if(effect)
        TaskBarTextDraw_SetColorVisual(playerid, index);    // Feedback Visual
    
    TaskBarTextDraw_SetSelected(playerid, index);
    CallLocalFunction("OnPlayerTaskBarDrawSelected", "ii", playerid, index);
}

stock TaskBarTextDraw_UnSelect(playerid) {

    Dialog_Hide(playerid);
    TaskBarTextDraw_SetSelected(playerid, -1);
    CallLocalFunction("OnPlayerTaskBarDrawUnSelected", "i", playerid);
}

static stock TaskBarTextDraw_SetColorVisual(playerid, index) {

    if(e_Data[playerid][E_DATA_COLOR_TIMER])
        TaskBarTextDraw_RestoreColor(playerid, e_Data[playerid][E_DATA_COLOR_INDEX]);

    TextDrawColour(SessionTextDrawData_GetDraw(index), TEXTDRAW_FEEDBACK);
    TextDrawShowForPlayer(playerid, SessionTextDrawData_GetDraw(index));

    e_Data[playerid][E_DATA_COLOR_INDEX] = index;
    e_Data[playerid][E_DATA_COLOR_TIMER] = SetTimerEx("OnTaskBar_RestoreColor", 1200, false, "ii", playerid, index);
}

static stock TaskBarTextDraw_RestoreColor(playerid, index) {
    TaskBarTextDraw_RestoreColorKillTimer(playerid);

    TextDrawColour(SessionTextDrawData_GetDraw(index), SessionTextDrawData_GetColor(index));
    TextDrawShowForPlayer(playerid, SessionTextDrawData_GetDraw(index));
}

static stock TaskBarTextDraw_RestoreColorKillTimer(playerid) {

    if(e_Data[playerid][E_DATA_COLOR_TIMER])
        KillTimer(e_Data[playerid][E_DATA_COLOR_TIMER]);

    e_Data[playerid][E_DATA_COLOR_TIMER] = 0;
}

stock TaskBarTextDraw_SetSelected(playerid, index) {

    if(e_Data[playerid][E_DATA_SELECTED_ID] == index)
        return;

    if(TaskBarTextDraw_Selected(playerid)) {
        new oldIndex = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDraw_RemoveSelect(playerid, oldIndex);
    }

    if(index != -1) SessionTextDraw_SetSelect(playerid, index);
    if(index == -1) TaskBarTextDraw_RestoreColorKillTimer(playerid);

    e_Data[playerid][E_DATA_SELECT] = index != -1;
    e_Data[playerid][E_DATA_SELECTED_ID] = index;
}

stock bool:TaskBarTextDraw_Selected(playerid)
    return e_Data[playerid][E_DATA_SELECT];

stock TaskBarTextDraw_GetSelected(playerid)
    return TaskBarTextDraw_Selected(playerid) ? e_Data[playerid][E_DATA_SELECTED_ID] : -1;

static stock TaskBarTextDraw_Reset(playerid) {

    TaskBarTextDraw_RestoreColorKillTimer(playerid);

    static const e_Clear[E_DATA];
    e_Data[playerid] = e_Clear;
}
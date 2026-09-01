
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnTaskBarMessage_Destroy(playerid);

static enum E_DATA {
    E_DATA_TIMER
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnUserLogout(playerid) {

    TaskBarMessage_Destroy(playerid);
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

public OnTaskBarMessage_Destroy(playerid)
    TaskBarMessage_Destroy(playerid);



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarMessage_Create(playerid, const string[], seconds) {

    if(TaskBarMessage_HasInfo(playerid))
        TaskBarMessage_Destroy(playerid, false);
    else
        TaskBarView_ShowInfo(playerid);

    TaskBarView_SetInfo(playerid, string);
    e_Data[playerid][E_DATA_TIMER] = SetTimerEx("OnTaskBarMessage_Destroy", 1000 * seconds, false, "i", playerid);
}

stock TaskBarMessage_Destroy(playerid, bool:hideDraw = true) {
    
    if(TaskBarMessage_HasInfo(playerid)) {
        KillTimer(e_Data[playerid][E_DATA_TIMER]);
    
        if(hideDraw)
            TaskBarView_HideInfo(playerid);
    }

    e_Data[playerid][E_DATA_TIMER] = 0;
}

static stock bool:TaskBarMessage_HasInfo(playerid)
    return e_Data[playerid][E_DATA_TIMER] > 0;
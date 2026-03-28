
            // Components
                // Types
#include "src/general/taskbar/components/types/align.inc"
#include "src/general/taskbar/components/types/buttons.inc"
#include "src/general/taskbar/components/types/font.inc"
#include "src/general/taskbar/components/types/itemType.inc"
#include "src/general/taskbar/components/types/mode.inc"
                //
#include "src/general/taskbar/components/header.inc"

            // Includes
#include <YSI_Coding\y_hooks>

hook OnUserLogin(playerid) {

    TaskBar_Create(playerid);
    // SendMessage(playerid, -1, ""#MESSAGE_GREEN"Press {CCCCCC}\"H\"{FFFFFF} to change the cursor and {CCCCCC}\"N\"{FFFFFF} to interact with the items.");
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnUserLogout(playerid) {

    TaskBar_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}


/*

                    .oooooo.   ooooo        ooooo   .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'  `Y8b  `888'        `888'  d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    888           888          888  888           888  d8'    Y88bo.      
                    888           888          888  888           88888[       `"Y8888o.  
                    888           888          888  888           888`88b.         `"Y88b 
                    `88b    ooo   888       o  888  `88b    ooo   888  `88b.  oo     .d8P 
                    `Y8bood8P'  o888ooooood8 o888o  `Y8bood8P'  o888o  o888o 8""88888P'  

*/

PlayerTextDrawClick:TaskBar_Buttons(playerid, E_TYPETASKBUTTON:type) {
    CallLocalFunction("OnPlayerTaskBarButton", "ii", playerid, _:type);
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

stock TaskBar_Create(playerid) {
    TextBarView_Create(playerid);
    TaskBar_Cursor(playerid, true);
}

stock TaskBar_Cursor(playerid, bool:status) {

    if(status)
        SelectTextDraw(playerid, TEXTDRAW_HOVER);
    else
        CancelSelectTextDraw(playerid);
    
    e_TaskBar[playerid][E_TASKBAR_CURSOR] = status;
}

stock bool:TaskBar_GetCursor(playerid)
    return e_TaskBar[playerid][E_TASKBAR_CURSOR];

static stock TaskBar_Reset(playerid) {

    static const e_Clear[E_TASKBAR];
    e_TaskBar[playerid] = e_Clear;
}

            // Components
                // Functions
#include "src/general/taskbar/components/functions/buttons.inc"
                // Events
#include "src/general/taskbar/components/events/projects.inc"
#include "src/general/taskbar/components/events/list.inc"

            // Views
#include "src/general/taskbar/views/default.inc"


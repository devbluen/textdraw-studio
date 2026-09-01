
            // Components
                // Types
#include "src/general/taskbar/components/types/align.inc"
#include "src/general/taskbar/components/types/button.inc"
#include "src/general/taskbar/components/types/font.inc"
#include "src/general/taskbar/components/types/type.inc"
#include "src/general/taskbar/components/types/mode.inc"
#include "src/general/taskbar/components/types/key.inc"
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

    if(!TaskBarButton_Enabled(playerid, type)) return;
    if(!TaskBarButton_IsDisplayed(playerid, type)) return;

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
    TaskBarView_Create(playerid);
    TaskBarEventSettings_SetMax(playerid, 413);
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

stock TaskBar_CursorToggle(playerid)
    TaskBar_Cursor(playerid, !TaskBar_GetCursor(playerid));

static stock TaskBar_Reset(playerid) {

    SessionPlayer_ResetLocalGroup(playerid);
    
    static const e_Clear[E_TASKBAR];
    e_TaskBar[playerid] = e_Clear;
}

            // Components
                // Functions
#include "src/general/taskbar/components/functions/buttons.inc"
#include "src/general/taskbar/components/functions/textdraw.inc"
#include "src/general/taskbar/components/functions/textdrawUpdate.inc"
#include "src/general/taskbar/components/functions/key.inc"
#include "src/general/taskbar/components/functions/message.inc"
                // Events
                    // Buttons
#include "src/general/taskbar/components/events/buttons/projects/projects.inc"
#include "src/general/taskbar/components/events/buttons/list.inc"
#include "src/general/taskbar/components/events/buttons/position_and_size.inc"
#include "src/general/taskbar/components/events/buttons/create.inc"
#include "src/general/taskbar/components/events/buttons/delete.inc"
#include "src/general/taskbar/components/events/buttons/mode.inc"
#include "src/general/taskbar/components/events/buttons/font.inc"
#include "src/general/taskbar/components/events/buttons/text.inc"
#include "src/general/taskbar/components/events/buttons/align.inc"
#include "src/general/taskbar/components/events/buttons/proportion.inc"
#include "src/general/taskbar/components/events/buttons/box.inc"
#include "src/general/taskbar/components/events/buttons/selectable.inc"
#include "src/general/taskbar/components/events/buttons/colors.inc"
#include "src/general/taskbar/components/events/buttons/copy.inc"
#include "src/general/taskbar/components/events/buttons/outline.inc"
#include "src/general/taskbar/components/events/buttons/shadow.inc"
#include "src/general/taskbar/components/events/buttons/model.inc"
#include "src/general/taskbar/components/events/buttons/groups.inc"
#include "src/general/taskbar/components/events/buttons/settings.inc"
                    //
#include "src/general/taskbar/components/events/moviment.inc"
#include "src/general/taskbar/components/events/update.inc"

            // Views
#include "src/general/taskbar/views/default.inc"

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_DATA_TASKBAR_Y,
    E_DATA_TASKBAR_MAX_Y
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_CONFIG)
        return Y_HOOKS_CONTINUE_RETURN_1;

    TaskBarEventSettings_Show(playerid);
    return Y_HOOKS_BREAK_RETURN_1;
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

stock TaskBarEventSettings_Show(playerid) {

    new 
        dialog[1024 + 1],
        dest[30 + 1]
    ;

    strcat(dialog, "Option\tOptional\n");

    Camera_GetNameByPlayer(playerid, dest);
    strcatEx(dialog, "Camera Mode\t{"#HEX_DEFAULT"}%s\n", dest);
    strcatEx(dialog, "Position\t{"#HEX_DEFAULT"}%d\n", TaskBarEventSettings_GetY(playerid));

    if(Session_Has()) {
        stringclear(dest);
        Session_GetPlayerVariable(dest);
        strcatEx(dialog, "Player Variable\t{"#HEX_DEFAULT"}%s\n", dest);

        stringclear(dest);
        Session_GetGlobalVariable(dest);
        strcatEx(dialog, "Global Variable\t{"#HEX_DEFAULT"}%s\n", dest);
    }

    Dialog_Show(playerid, D_SETTINGS, DIALOG_STYLE_TABLIST_HEADERS, "Settings", dialog, "Select", "Close");
}

stock TaskBarEventSettings_SetMax(playerid, max)
    e_Data[playerid][E_DATA_TASKBAR_MAX_Y] = max;

stock TaskBarEventSettings_SetY(playerid, offset) {
    
    new maxValue = TaskBarEventSettings_GetMaxY(playerid);

    if(offset < 0) offset = 0;
    else if(offset > maxValue) offset = maxValue;
    
    e_Data[playerid][E_DATA_TASKBAR_Y] = offset;
    TaskBarView_SetPosition(playerid, offset);
}

stock TaskBarEventSettings_GetMaxY(playerid)
    return e_Data[playerid][E_DATA_TASKBAR_MAX_Y];

stock TaskBarEventSettings_GetY(playerid)
    return e_Data[playerid][E_DATA_TASKBAR_Y];



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_SETTINGS(playerid, response, listitem) {

    if(response) {

        switch(listitem) {
            case 0: Camera_Show(playerid);
            case 1: TaskBarKey_Set(playerid, E_TYPEKEY_TASKBAR);
            case 2: Dialog_Show(playerid, D_SETTINGS_VPLAYER, DIALOG_STYLE_INPUT, "Player Variable", "Please enter the name of the variable you want below.", "Change", "Previous");
            case 3: Dialog_Show(playerid, D_SETTINGS_VGLOBAL, DIALOG_STYLE_INPUT, "Global Variable", "Please enter the name of the variable you want below.", "Change", "Previous");
        }
    }
    return true;
}

Dialog:D_SETTINGS_VPLAYER(playerid, response, listitem, inputtext[]) {
    
    if(response && !isnull(inputtext)) 
        Session_SetPlayerVariable(inputtext);
        
    TaskBarEventSettings_Show(playerid);
}

Dialog:D_SETTINGS_VGLOBAL(playerid, response, listitem, inputtext[]) {
    
    if(response && !isnull(inputtext))
        Session_SetGlobalVariable(inputtext);
    
    TaskBarEventSettings_Show(playerid);
}
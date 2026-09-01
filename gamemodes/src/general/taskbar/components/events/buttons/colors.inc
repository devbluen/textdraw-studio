
            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DATA {
    E_TYPETASKBUTTON:E_DATA_TYPE_BUTTON
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_COLOR && type != E_TYPETASKBUTTON_COLOR_BG && type != E_TYPETASKBUTTON_COLOR_BOX)    
        return Y_HOOKS_CONTINUE_RETURN_1;

    e_Data[playerid][E_DATA_TYPE_BUTTON] = type;

    TaskBarEventColors_Show(playerid);
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

static stock TaskBarEventColors_Show(playerid)
    Util_WebColorCreate(playerid, "DRAWSCOLOR");

static stock E_TYPETASKBUTTON:TaskBarEventColors_GetButton(playerid)
    return e_Data[playerid][E_DATA_TYPE_BUTTON];



/*

                    .oooooo.     .oooooo.   ooooo          .oooooo.   ooooooooo.    .oooooo..o 
                    d8P'  `Y8b   d8P'  `Y8b  `888'         d8P'  `Y8b  `888   `Y88. d8P'    `Y8 
                    888          888      888  888         888      888  888   .d88' Y88bo.      
                    888          888      888  888         888      888  888ooo88P'   `"Y8888o.  
                    888          888      888  888         888      888  888`88b.         `"Y88b 
                    `88b    ooo  `88b    d88'  888       o `88b    d88'  888  `88b.  oo     .d8P 
                    `Y8bood8P'   `Y8bood8P'  o888ooooood8  `Y8bood8P'  o888o  o888o 8""88888P'  

*/

WebColor:DRAWSCOLOR(playerid, color) {

    new E_TYPETASKBUTTON:typeButton = TaskBarEventColors_GetButton(playerid);

    if(color == -2) TaskBarKey_Set(playerid, TaskBarTextDrawUpdate_GetKeyByButton(typeButton)); 
    else if(color == -3) return;    // TaskBarEventColors_Show(playerid);
    else
    {
        new currentIndex = TaskBarTextDraw_GetSelected(playerid);
        TaskBarTextDrawUpdate_SetColor(typeButton, currentIndex, color);
    }
}
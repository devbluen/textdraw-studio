
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_COPY)
        return Y_HOOKS_CONTINUE_RETURN_1;

    Dialog_Show(playerid, D_TASKCOPY, DIALOG_STYLE_MSGBOX, "Copy", "Do you really want to copy this textdraw?", "Yes", "Cancel");
    return Y_HOOKS_BREAK_RETURN_1;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_TASKCOPY(playerid, response, listitem) {

    if(response) {
        new 
            currentIndex = TaskBarTextDraw_GetSelected(playerid),
            index = SessionTextDrawData_Copy(currentIndex)
        ;

        TaskBarTextDraw_Select(playerid, index);
        SendMessage(playerid, -1, ""#MESSAGE_GREEN"Textdraw copied successfully.");
    }
    return true;
}

            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_DELETE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    Dialog_Show(playerid, D_ITEM_DELETE, DIALOG_STYLE_MSGBOX, L(playerid, E_LANG_DEL_TITLE), L(playerid, E_LANG_DEL_BODY), L(playerid, E_LANG_BTN_DELETE), L(playerid, E_LANG_BTN_CANCEL));
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

Dialog:D_ITEM_DELETE(playerid, response) {

    if(response) {
        new 
            index = TaskBarTextDraw_GetSelected(playerid),
            nextIndex = SessionTextDraw_GetPrevious(index)
        ;

        SessionTextDrawData_Destroy(index);

        if(nextIndex != ITER_NONE && nextIndex != SessionTextDraw_GetMax())
            TaskBarTextDraw_Select(playerid, nextIndex);
    }
    return true;
}

            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_OUTLINE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new 
        dialog[57 * 5],
        index = TaskBarTextDraw_GetSelected(playerid)
    ;

    LangF(playerid, dialog, sizeof dialog, E_LANG_OUTLINE_BODY, SessionTextDrawData_GetOutline(index));

    Dialog_Show(playerid, D_ITEM_OUTLINE, DIALOG_STYLE_INPUT, L(playerid, E_LANG_OUTLINE), dialog, L(playerid, E_LANG_BTN_CHANGE), L(playerid, E_LANG_BTN_CANCEL));
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

Dialog:D_ITEM_OUTLINE(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new outline;
        if(sscanf(inputtext, "d", outline))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_ONLY_NUMBERS));

        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetOutline(index, outline);
    }
    return true;
}
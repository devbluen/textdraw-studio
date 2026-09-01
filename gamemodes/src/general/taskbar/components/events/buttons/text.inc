
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_TEXT)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new 
        index = TaskBarTextDraw_GetSelected(playerid),
        string[1024 * 4],
        dialog[54 + sizeof string + 1]
    ;

    SessionTextDrawData_GetString(index, string);
    format(dialog, sizeof dialog, "Which text do you want?\n\n{f52746}Current:\n{FFFFFF} %s", string);

    Dialog_Show(playerid, D_ITEM_TEXT, DIALOG_STYLE_INPUT, "Change Text", dialog, "Change", "Cancel");
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

Dialog:D_ITEM_TEXT(playerid, response, listitem, inputtext[]) {

    if(response && !isnull(inputtext)) {

        new index = TaskBarTextDraw_GetSelected(playerid);
        SessionTextDrawData_SetString(index, inputtext);
    }
    return true;
}
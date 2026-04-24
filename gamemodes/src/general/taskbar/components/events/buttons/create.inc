
            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type) {

    if(type != E_TYPETASKBUTTON_CREATE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new dialog[64 * 4];
    strcat(dialog, "Normal Textdraw\n");
    strcat(dialog, "Sprite Browser {CCCCCC}(TXD and Custom TXD's)\n");
    strcat(dialog, "Models {CCCCCC}(Objects, Vehicles and Actors)\n");
    strcat(dialog, "Create Sprite White (default)");

    Dialog_Show(playerid, D_CREATION, DIALOG_STYLE_TABLIST, "Creation", dialog, "Select", "Cancel");
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

Dialog:D_CREATION(playerid, response, listitem, inputtext[]) {

    if(response) {

        new index;

        switch(listitem) {
            case 0: index = SessionTextDrawData_Create(E_TYPEITEM_TEXT);
            case 1: {SpriteBrowser_Show(playerid); return true;}
            case 2: index = SessionTextDrawData_Create(E_TYPEITEM_MODEL);
            case 3: index = SessionTextDrawData_Create(E_TYPEITEM_SPRITE);
        }
    
        TaskBarTextDraw_Select(playerid, index, false);
    }
    return true;
}
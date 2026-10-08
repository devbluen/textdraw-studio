
// Includes
#include <YSI_Coding\y_hooks>
hook OnPlayerTaskBarButton(playerid, E_TYPETASKBUTTON:type)
{

    if (type != E_TYPETASKBUTTON_CREATE)
        return Y_HOOKS_CONTINUE_RETURN_1;

    new dialog[64 * 5];
    strcatEx(dialog, "%s\n", L(playerid, E_LANG_CREATE_NORMAL));
    strcatEx(dialog, "%s\n", L(playerid, E_LANG_CREATE_SPRITE_BROWSER));
    strcatEx(dialog, "%s\n", L(playerid, E_LANG_CREATE_MODELS));
    strcatEx(dialog, "%s\n", L(playerid, E_LANG_CREATE_SPRITE_WHITE));
    strcat(dialog, L(playerid, E_LANG_CREATE_PROGRESS));

    Dialog_Show(playerid, D_CREATION, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_CREATION), dialog, L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL));
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

Dialog:D_PROGRESS_CREATE(playerid, response, listitem, inputtext[])
{

    if (response)
    {

        new index;

        switch (listitem)
        {
            case 0: index = SessionTextDrawData_Create(E_TYPEITEM_CIRCLE);
            case 1: index = SessionTextDrawData_Create(E_TYPEITEM_HEXAGON);
            case 2: index = SessionTextDrawData_Create(E_TYPEITEM_DIAMOND);
            case 3: index = SessionTextDrawData_Create(E_TYPEITEM_SQUARE);
            case 4: index = SessionTextDrawData_Create(E_TYPEITEM_TRIANGLE);
            case 5: index = SessionTextDrawData_Create(E_TYPEITEM_PARENS);
            case 6: index = SessionTextDrawData_Create(E_TYPEITEM_ARC);
        }

        TaskBarTextDraw_Select(playerid, index, false);
    }
    return true;
}

Dialog:D_CREATION(playerid, response, listitem, inputtext[])
{

    if (response)
    {

        new index;

        switch (listitem)
        {
            case 0: index = SessionTextDrawData_Create(E_TYPEITEM_TEXT);
            case 1:
            {
                SpriteBrowser_Show(playerid);
                return true;
            }
            case 2: index = SessionTextDrawData_Create(E_TYPEITEM_MODEL);
            case 3: index = SessionTextDrawData_Create(E_TYPEITEM_SPRITE);
            case 4:
            {
                new dialog[64 * 7];
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_CIRCLE));
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_HEXAGON));
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_DIAMOND));
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_SQUARE));
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_TRIANGLE));
                strcatEx(dialog, "%s\n", L(playerid, E_LANG_PROGRESS_PARENS));
                strcat(dialog, L(playerid, E_LANG_PROGRESS_ARC));
                Dialog_Show(playerid, D_PROGRESS_CREATE, DIALOG_STYLE_TABLIST, L(playerid, E_LANG_PROGRESS_TITLE), dialog, L(playerid, E_LANG_BTN_SELECT), L(playerid, E_LANG_BTN_CANCEL));
                return true;
            }
        }

        TaskBarTextDraw_Select(playerid, index, false);
    }
    return true;
}
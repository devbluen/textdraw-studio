
            // Components
#include "src/general/misc/dialog/components/header.inc"

            // Includes
#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason) {

    DialogMod_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
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

stock DialogMod_Create(playerid, DIALOG_STYLE:style, const title[], const button1[], const button2[], const callback[], Func:callbackCreate<>) {

    DialogMod_Reset(playerid);

    Indirect_Claim(callbackCreate);
    @.callbackCreate();
    Indirect_Release(callbackCreate);

    strcopy(e_DialogMod[playerid][E_DIALOGMOD_CALLBACK], callback);
    e_DialogMod[playerid][E_DIALOGMOD_STYLE] = style;

    new dialog[1024 * 4];
    foreach(new i: DialogModItens[playerid]) {
        strcat(dialog, e_DialogModItem[playerid][i][E_DIALOGMODITEM_STRING]);
    }

    Dialog_Show(playerid, D_DIALOGMOD, style, title, dialog, button1, button2);
}

stock DialogMod_Add(playerid, const string[], params = -1, {Float, _}:...) {

    new index = Iter_Free(DialogModItens[playerid]);
    if(index == ITER_NONE)
        return;

    new string_buff[256 + 1];
    format(string_buff, sizeof string_buff, string, ___(3));
    strcat(string_buff, "\n");

    e_DialogModItem[playerid][index][E_DIALOGMODITEM_PARAMS] = params;
    strcopy(e_DialogModItem[playerid][index][E_DIALOGMODITEM_STRING], string_buff);

    Iter_Add(DialogModItens[playerid], index);
}

static stock DialogMod_Reset(playerid) {

    foreach(new i: DialogModItens[playerid]) {
        static const e_ClearItem[E_DIALOGMODITEM];
        e_DialogModItem[playerid][i] = e_ClearItem;
    }

    static const e_Clear[E_DIALOGMOD];
    e_DialogMod[playerid] = e_Clear;

    Iter_Clear(DialogModItens[playerid]);
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

Dialog:D_DIALOGMOD(playerid, response, listitem, inputtext[]) {

    new 
        fisListitem = (e_DialogMod[playerid][E_DIALOGMOD_STYLE] == DIALOG_STYLE_TABLIST_HEADERS ? (1) : (0)),
        params = e_DialogModItem[playerid][listitem + fisListitem][E_DIALOGMODITEM_PARAMS],
        callback[30 + 1]
    ;

    strcatEx(callback, "dlmo_%s", e_DialogMod[playerid][E_DIALOGMOD_CALLBACK]);

    DialogMod_Reset(playerid);
    CallLocalFunction(callback, "iisi", playerid, response, inputtext, params);
    return true;
}
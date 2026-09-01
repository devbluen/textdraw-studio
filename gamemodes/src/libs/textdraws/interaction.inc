
            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnPlayerTextdrawClose(playerid);

static enum E_TEXTDRAW_DATA {
    E_TEXTDRAW_DATA_SELECTIONS,
    E_TEXTDRAW_DATA_COLOR,
    E_TEXTDRAW_DATA_WAIT,
    bool:E_TEXTDRAW_DATA_CANCEL
};

static e_TextdrawData[MAX_PLAYERS][E_TEXTDRAW_DATA];

hook OnPlayerDisconnect(playerid, reason) {
    
    TextDrawReset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;   
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {

    if(clickedid == INVALID_TEXT_DRAW) {
        
        if(e_TextdrawData[playerid][E_TEXTDRAW_DATA_CANCEL]) {
            e_TextdrawData[playerid][E_TEXTDRAW_DATA_CANCEL] = false;
            return Y_HOOKS_BREAK_RETURN_1;
        }

        if(!SelectedTextDraw(playerid))
            return Y_HOOKS_BREAK_RETURN_1;

        if(e_TextdrawData[playerid][E_TEXTDRAW_DATA_WAIT] >= gettime()) {
            ReSelectTextDraw(playerid);
            return Y_HOOKS_BREAK_RETURN_1;
        }

        CallLocalFunction("OnPlayerTextdrawClose", "i", playerid);

        if(e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS])
            ReSelectTextDraw(playerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {
    if(Dialog_Opened(playerid)) 
        return Y_HOOKS_BREAK_RETURN_1;

    if(!SelectedTextDraw(playerid))
        return Y_HOOKS_BREAK_RETURN_1;

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

stock SelectedTextDraw(playerid)
    return e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS] > 0;

static stock TextDrawReset(playerid) {

    static const e_Clear[E_TEXTDRAW_DATA];
    e_TextdrawData[playerid] = e_Clear;
}

static stock ReSelectTextDraw(playerid) {
    if(!SelectedTextDraw(playerid))
        return;
    
    SelectTextDraw(playerid, e_TextdrawData[playerid][E_TEXTDRAW_DATA_COLOR]);
}



/*

                    ooo        ooooo       .o.         .oooooo.   ooooooooo.     .oooooo.    .oooooo..o 
                    `88.       .888'      .888.       d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 
                    888b     d'888      .8"888.     888           888   .d88' 888      888 Y88bo.      
                    8 Y88. .P  888     .8' `888.    888           888ooo88P'  888      888  `"Y8888o.  
                    8  `888'   888    .88ooo8888.   888           888`88b.    888      888      `"Y88b 
                    8    Y     888   .8'     `888.  `88b    ooo   888  `88b.  `88b    d88' oo     .d8P 
                    o8o        o888o o88o     o8888o  `Y8bood8P'  o888o  o888o  `Y8bood8P'  8""88888P'  

*/

stock alias_SelectTextDraw(playerid, hovercolor) {

    e_TextdrawData[playerid][E_TEXTDRAW_DATA_WAIT] = gettime() + 2;
    e_TextdrawData[playerid][E_TEXTDRAW_DATA_COLOR] = hovercolor;
    e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS]++;

    SelectTextDraw(playerid, hovercolor);
    return true;
}

#if defined _ALS_SelectTextDraw
    #undef SelectTextDraw
#else
    #define _ALS_SelectTextDraw
#endif
 
#define SelectTextDraw alias_SelectTextDraw

stock alias_CancelSelectTextDraw(playerid) {
    if(!e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS])
        return false;

    e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS]--;
    if(!e_TextdrawData[playerid][E_TEXTDRAW_DATA_SELECTIONS]) {

        e_TextdrawData[playerid][E_TEXTDRAW_DATA_CANCEL] = true;
        CancelSelectTextDraw(playerid);
    }
    return true;
}

#if defined _ALS_CancelSelectTextDraw
    #undef CancelSelectTextDraw
#else
    #define _ALS_CancelSelectTextDraw
#endif
 
#define CancelSelectTextDraw alias_CancelSelectTextDraw
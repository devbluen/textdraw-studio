
static enum E_DATA {
    E_DATA_MAX_PLAYER,
    E_DATA_MAX_GLOBAL
};

static
    e_Data[MAX_PLAYERS][E_DATA]
;


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock TaskBarEventProjectExport_Show(playerid) {

    new 
        dialog[1024],
        uniqueId = Session_GetId(),
        name[30 + 1]
    ;

    Session_GetName(name);
    strcatEx(dialog, "{FFFFFF}Default: {"#HEX_DEFAULT"}%s.txt{FFFFFF}\n", name);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            COUNT(*) FILTER (WHERE mode = %i) AS player, \
                                                            COUNT(*) FILTER (WHERE mode = %i) AS global \
                                                        FROM textdraws \
                                                        WHERE project_id = %i", 
                                                        
                                                        _:E_TYPEMODE_PLAYER,
                                                        _:E_TYPEMODE_GLOBAL,
                                                        uniqueId
                                                    );

    if(cache)
    {
        e_Data[playerid][E_DATA_MAX_PLAYER] = DB_GetFieldIntByName(cache, "player");
        e_Data[playerid][E_DATA_MAX_GLOBAL] = DB_GetFieldIntByName(cache, "global");
        
        strcatEx(dialog, "Player Textdraws: {"#HEX_DEFAULT"}%d{FFFFFF}\n", e_Data[playerid][E_DATA_MAX_PLAYER]);
        strcatEx(dialog, "Global Textdraws: {"#HEX_DEFAULT"}%d{FFFFFF}\n", e_Data[playerid][E_DATA_MAX_GLOBAL]);
        DB_FreeResultSet(cache);
    }

    strcat(dialog, "\nPlease enter the desired export name below.");
    Dialog_Show(playerid, D_TASKBAR_EXPORT, DIALOG_STYLE_INPUT, "Export", dialog, "Export", "Previous");
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

Dialog:D_TASKBAR_EXPORT(playerid, response, listitem, inputtext[]) {

    if(response) {

        new name[30 + 1];
        Session_GetName(name);

        if(!isnull(inputtext)) {
            
            if(strlen(inputtext) > 30) 
                return Dialog_ReShow(playerid, "The name size is too large (Max: 30)");

            strcopy(name, inputtext);
        }

        new uniqueId = Session_GetId();

        SessionTextDrawExport_Create(uniqueId, name, e_Data[playerid][E_DATA_MAX_PLAYER], e_Data[playerid][E_DATA_MAX_GLOBAL]);
        SendMessage(INVALID_PLAYER_ID, -1, ""MESSAGE_GREEN"Project {CCCCCC}\"%s\"{FFFFFF} was successfully exported, please check the scriptfiles folder.", name);
    }

    TaskBarEventProjectLoad_Show(playerid);
    return true;
}
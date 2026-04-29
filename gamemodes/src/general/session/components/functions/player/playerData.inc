


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionPlayerData_SetPosition(playerid, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionPlayersGroups[playerid]) {
        SessionTextDrawData_GetPosition(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else TaskBarEvent_MultipleOptions(playerid);

        SessionTextDrawData_SetPosition(i, position[0], position[1], execute_query);
    }
}

stock SessionPlayerData_SetSize(playerid, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionPlayersGroups[playerid]) {
        SessionTextDrawData_GetSize(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else TaskBarEvent_MultipleOptions(playerid);

        SessionTextDrawData_SetSize(i, position[0], position[1], execute_query);
    }
}

stock SessionPlayerData_SetLetterSize(playerid, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionPlayersGroups[playerid]) {
        SessionTextDrawData_GetLettSize(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else TaskBarEvent_MultipleOptions(playerid);
        
        SessionTextDrawData_SetLettSize(i, position[0], position[1], execute_query);
    }
}

stock SessionPlayerData_SetColor(playerid, color, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetColor(i, color, execute_query);
}

stock SessionPlayerData_SetColorBG(playerid, color, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetColorBG(i, color, execute_query);
}

stock SessionPlayerData_SetColorBox(playerid, color, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetColorBox(i, color, execute_query);
}

stock SessionPlayerData_SetBox(playerid, bool:status, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetBox(i, status, execute_query);
}

stock SessionPlayerData_SetFont(playerid, E_TYPEFONT:font, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetFont(i, font, execute_query);
}

stock SessionPlayerData_SetAlign(playerid, E_TYPEALIGNMENT:type, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetAlign(i, type, execute_query);
}

stock SessionPlayerData_SetPropor(playerid, bool:status, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetPropor(i, status, execute_query);
}

stock SessionPlayerData_SetMode(playerid, E_TYPEMODE:type, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetMode(i, type, execute_query);
}

stock SessionPlayerData_SetString(playerid, const string[], bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetString(i, string, execute_query);
}

stock SessionPlayerData_SetOutline(playerid, value, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetOutline(i, value, execute_query);
}

stock SessionPlayerData_SetShadow(playerid, value, bool:execute_query = true) {
    foreach(new i: SessionPlayersGroups[playerid]) 
        SessionTextDrawData_SetShadow(i, value, execute_query);
}
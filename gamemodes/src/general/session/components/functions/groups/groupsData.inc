


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionGroupDataDraw_SetText(index, const string[], bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetString(i, string, execute_query);
}

stock SessionGroupDataDraw_SetVariable(index, const string[], bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetVariable(i, string, execute_query);   
}

stock SessionGroupDataDraw_SetMode(index, E_TYPEMODE:type, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetMode(i, type, execute_query);
}

stock SessionGroupDataDraw_SetBox(index, bool:status, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetBox(i, status, execute_query);
}

stock SessionGroupDataDraw_SetSelect(index, bool:status, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetSelect(i, status, execute_query);
}

stock SessionGroupDataDraw_SetColor(index, color, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetColor(i, color, execute_query);
}

stock SessionGroupDataDraw_SetColorBG(index, color, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetColorBG(i, color, execute_query);
}

stock SessionGroupDataDraw_SetColorBox(index, color, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetColorBox(i, color, execute_query);
}

stock SessionGroupDataDraw_SetPosition(playerid, index, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionGroupsDraws[index]) {
        SessionTextDrawData_GetPosition(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else SessionEventGroupItem_Options(playerid);

        SessionTextDrawData_SetPosition(i, position[0], position[1], execute_query);
    }
}

stock SessionGroupDataDraw_SetSize(playerid, index, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionGroupsDraws[index]) {
        SessionTextDrawData_GetSize(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else SessionEventGroupItem_Options(playerid);

        SessionTextDrawData_SetSize(i, position[0], position[1], execute_query);
    }
}

stock SessionGroupDataDraw_SetLettSize(playerid, index, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionGroupsDraws[index]) {
        SessionTextDrawData_GetLettSize(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        else SessionEventGroupItem_Options(playerid);
        
        SessionTextDrawData_SetLettSize(i, position[0], position[1], execute_query);
    }
}

stock SessionGroupDataDraw_SetFont(index, E_TYPEFONT:font, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetFont(i, font, execute_query);
}

stock SessionGroupDataDraw_SetAlign(index, E_TYPEALIGNMENT:align, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetAlign(i, align, execute_query);
}

stock SessionGroupDataDraw_SetPropor(index, bool:status, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetPropor(i, status, execute_query);
}

stock SessionGroupDataDraw_SetOuline(index, value, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetOutline(i, value, execute_query);
}

stock SessionGroupDataDraw_SetShadow(index, value, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[index])
        SessionTextDrawData_SetShadow(i, value, execute_query);
}
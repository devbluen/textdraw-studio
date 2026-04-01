


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionPlayer_AddDraw(playerid, indexDraw)
    Iter_Add(SessionPlayersGroups[playerid], indexDraw);

stock SessionPlayer_RemoveDraw(playerid, indexDraw)
    Iter_Remove(SessionPlayersGroups[playerid], indexDraw);

stock bool:SessionPlayer_HasAny(playerid)
    return !Iter_IsEmpty(SessionPlayersGroups[playerid]);

stock bool:SessionPlayer_Has(playerid, indexDraw)
    return Iter_Contains(SessionPlayersGroups[playerid], indexDraw);

stock SessionPlayer_SetPosition(playerid, Float:offsetX, Float:offsetY, bool:execute_query = true, bool:onlySave = false) {

    new Float:position[2];
    foreach(new i: SessionPlayersGroups[playerid]) {
        SessionTextDrawData_GetPosition(i, position[0], position[1]);
        if(!onlySave) {
            position[0] += offsetX;
            position[1] += offsetY;
        }
        SessionTextDrawData_SetPosition(i, position[0], position[1], execute_query);
    }
}

stock SessionPlayer_OpenListGroups(playerid)
    SessionEventGroupList_Show(playerid, "OPEN_PROJECT");

stock SessionPlayer_AddWithSelected(playerid)
    SessionEventGroupList_Show(playerid, "SET_SELECTED_ON_GROUP");

stock SessionPlayer_ResetLocalGroup(playerid)
    Iter_Clear(SessionPlayersGroups[playerid]);

stock SessionPlayer_SelectAll(playerid) {
    
    foreach(new i: SessionDraws)
        SessionPlayer_AddDraw(playerid, i);
}

stock SessionPlayer_DestroyAll(playerid) {

    foreach(new i: SessionPlayersGroups[playerid])
        SessionTextDrawData_Destroy(i);
}

stock SessionPlayer_CloneAll(playerid, bool:choose = false) {

    new 
        index,
        Iterator:tempGroups<MAX_TEXTDRAWS_STUDIO>
    ;

    foreach(new i: SessionPlayersGroups[playerid]) {
        index = SessionTextDrawData_Copy(i);

        if(choose) {
            SessionPlayer_RemoveDraw(playerid, i);
            Iter_Add(tempGroups, index);
        }
    }

    if(choose) {
        foreach(new i: tempGroups)
            SessionPlayer_AddDraw(playerid, i);
    }
}



/*

                    .oooooo.    ooooooooo.     .oooooo.   ooooo     ooo ooooooooo.   
                    d8P'  `Y8b   `888   `Y88.  d8P'  `Y8b  `888'     `8' `888   `Y88. 
                    888            888   .d88' 888      888  888       8   888   .d88' 
                    888            888ooo88P'  888      888  888       8   888ooo88P'  
                    888     ooooo  888`88b.    888      888  888       8   888         
                    `88.    .88'   888  `88b.  `88b    d88'  `88.    .8'   888         
                    `Y8bood8P'   o888o  o888o  `Y8bood8P'     `YbodP'    o888o        

*/

Group:OPEN_PROJECT(playerid, indexGroup) {
    SessionEventGroupItem_Show(playerid, indexGroup);
}

Group:SET_SELECTED_ON_GROUP(playerid, indexGroup) {

    foreach(new i: SessionPlayersGroups[playerid]) {
        if(SessionGroup_HasDrawId(indexGroup, i))
            continue;

        SessionGroup_AddDraw(indexGroup, i);
    }

    SessionEventGroupItem_Show(playerid, indexGroup);
}
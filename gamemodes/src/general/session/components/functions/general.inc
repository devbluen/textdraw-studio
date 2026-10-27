


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Session_Create(uniqueId) {
    if(Session_Has())
        Session_Destroy();

    Session_SetId(uniqueId);

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            name, \
                                                            globalVariable, \
                                                            playerVariable \
                                                        FROM projects \
                                                        WHERE id = %i", 

                                                        uniqueId
                                                    );

    if(cache)
    {
        DB_GetFieldStringByName(cache, "name", e_Session[E_SESSION_NAME]);
        DB_GetFieldStringByName(cache, "playerVariable", e_Session[E_SESSION_PLAYER_VARIABLE]);
        DB_GetFieldStringByName(cache, "globalVariable", e_Session[E_SESSION_GLOBAL_VARIABLE]);
        DB_FreeResultSet(cache);

        SessionTextDrawData_LoadAll();
        SessionTextDraw_UpdateButtonAll();
        SessionGroup_LoadAll();

        Undo_Init();
    }
}

stock Session_Destroy() {
    Session_SetId(0);

    SessionTextDraw_DestroyAll();
    SessionGroup_DestroyAll();

    Undo_Reset();
}

stock Session_ReloadAll() {

    if(!Session_Has())
        return;

    new selected[MAX_PLAYERS];
    foreach(new i: Users)
        selected[i] = TaskBarTextDraw_GetSelected(i);

    SessionTextDraw_DestroyAll();
    SessionGroup_DestroyAll();
    Iter_Clear(SessionGroups);

    SessionTextDrawData_LoadAll();
    SessionGroup_LoadAll();

    foreach(new i: Users) {

        // Drop any local selection that points to a textdraw that no longer exists
        new stale[MAX_TEXTDRAWS_STUDIO], staleCount;

        foreach(new j: SessionPlayersGroups[i]) {
            if(!SessionTextDrawData_Has(j))
                stale[staleCount++] = j;
        }

        for(new j; j < staleCount; j++)
            SessionPlayer_RemoveDraw(i, stale[j]);

        if(selected[i] != -1 && SessionTextDrawData_Has(selected[i]))
            TaskBarTextDraw_Select(i, selected[i], false);
        else
            TaskBarTextDraw_UnSelect(i);
    }

    SessionTextDraw_UpdateButtonAll();
}

stock Session_SetId(uniqueId)
    e_Session[E_SESSION_ID] = uniqueId;

stock Session_SetGlobalVariable(const string[])
    strcopy(e_Session[E_SESSION_GLOBAL_VARIABLE], string);

stock Session_SetPlayerVariable(const string[])
    strcopy(e_Session[E_SESSION_PLAYER_VARIABLE], string);

stock Session_GetGlobalVariable(dest[], maxLength = sizeof dest)
    strcat(dest, e_Session[E_SESSION_GLOBAL_VARIABLE], maxLength);

stock Session_GetPlayerVariable(dest[], maxLength = sizeof dest)
    strcat(dest, e_Session[E_SESSION_PLAYER_VARIABLE], maxLength);

stock Session_GetName(dest[], maxLength = sizeof dest)
    strcat(dest, e_Session[E_SESSION_NAME], maxLength);

stock Session_GetId()
    return e_Session[E_SESSION_ID];

stock bool:Session_Has()
    return Session_GetId() > 0;
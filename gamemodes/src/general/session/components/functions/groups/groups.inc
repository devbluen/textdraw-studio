


/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock SessionGroup_LoadAll() {

    new uniqueId = Session_GetId();

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            id \
                                                        FROM groups \
                                                        WHERE project_id = %i",

                                                        uniqueId
                                                    );

    if(cache)
    {
        if(DB_GetRowCount(cache))
        {
            new id;

            do
            {
                id = DB_GetFieldIntByName(cache, "id");
                SessionGroup_Load(id);    
            }
            while(DB_SelectNextRow(cache));
        }

        DB_FreeResultSet(cache);
    }
}
 
stock SessionGroup_Create(uniqueId, const name[]) {
    new index = Iter_Free(SessionGroups);
    if(index == ITER_NONE)
        return -1;

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "INSERT INTO groups (project_id, name, indexGroup) VALUES (%i, '%s', %i)", uniqueId, name, index);
    if(cache)
        DB_FreeResultSet(cache);

    new insertId = SessionGroup_GetGenId(uniqueId);
    if(insertId)
        SessionGroup_Load(insertId);

    return index;
}

stock SessionGroup_Destroy(index, bool:execute_query = true) {
    
    if(execute_query) {
        DB_FreeResultSet(
            DB_ExecuteQuery(IDConnection, "DELETE FROM groups WHERE id = %i", SessionGroup_GetUniqueId(index))
        );
    }

    SessionGroup_RemoveAll(index, false);
    Iter_Remove(SessionGroups, index);

    static const e_Clear[E_SESSIONGROUP];
    e_SessionGroup[index] = e_Clear;
}

stock SessionGroup_DestroyBySession(uniqueId) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "DELETE FROM groups WHERE project_id = %i", uniqueId);
    if(cache)
        DB_FreeResultSet(cache);

    Iter_Clear(SessionGroups);
}

static stock SessionGroup_Load(groupId) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT \
                                                            name, \
                                                            indexGroup \
                                                        FROM groups \
                                                        WHERE id = %i",

                                                        groupId
                                                    );

    if(cache)
    {
        if(DB_GetRowCount(cache))
        {
            new index = DB_GetFieldIntByName(cache, "indexGroup");

            e_SessionGroup[index][E_SESSIONGROUP_UNIQUE_ID] = groupId;
            DB_GetFieldStringByName(cache, "name", e_SessionGroup[index][E_SESSIONGROUP_NAME]);
        
            Iter_Add(SessionGroups, index);
            
            new DBResult:cacheEx = DB_ExecuteQuery(IDConnection, "SELECT \
                                                                    t.indexDraw \
                                                                FROM groups_textdraws gt \
                                                                JOIN textdraws t ON t.id = gt.draw_id \
                                                                WHERE gt.group_id = %i",
                                                                
                                                                groupId
                                                            );

            if(cacheEx)
            {
                if(DB_GetRowCount(cacheEx))
                {
                    new drawId;

                    do
                    {
                        drawId = DB_GetFieldIntByName(cacheEx, "indexDraw");
                        SessionGroup_AddDraw(index, drawId, false);
                    }
                    while(DB_SelectNextRow(cacheEx));
                }

                DB_FreeResultSet(cacheEx);
            }
        }

        DB_FreeResultSet(cache);
    }
}

stock SessionGroup_AddDraw(indexGroup, indexDraw, bool:execute_query = true) {

    if(execute_query) {
        
        DB_FreeResultSet(
            DB_ExecuteQuery(
                IDConnection, 
                "INSERT INTO groups_textdraws (group_id, draw_id) VALUES (%i, %i)", 
                    SessionGroup_GetUniqueId(indexGroup),
                    SessionTextDrawData_GetUniqueId(indexDraw)
            )
        );
    }

    Iter_Add(SessionGroupsDraws[indexGroup], indexDraw);
}

stock SessionGroup_RemoveDraw(indexGroup, indexDraw, bool:execute_query = true) {

    if(execute_query) {

        DB_FreeResultSet(
            DB_ExecuteQuery(
                IDConnection, 
                "DELETE FROM groups_textdraws WHERE group_id = %i AND draw_id = %i",
                    SessionGroup_GetUniqueId(indexGroup), 
                    SessionTextDrawData_GetUniqueId(indexDraw)
            )
        );
    }

    Iter_Remove(SessionGroupsDraws[indexGroup], indexDraw);
}

stock SessionGroup_RemoveAll(indexGroup, bool:execute_query = true) {

    foreach(new i: SessionGroupsDraws[indexGroup])
        SessionGroup_RemoveDraw(indexGroup, i, execute_query);
}

stock SessionGroup_DestroyDraws(indexGroup) {

    foreach(new i: SessionGroupsDraws[indexGroup]) {
        SessionTextDrawData_Destroy(i);
        SessionGroup_RemoveDraw(indexGroup, i, false);
    }
}

stock SessionGroup_RemoveAllByDrawIndex(indexDraw, bool:execute_query = true) {

    foreach(new i: SessionGroups)
        if(SessionGroup_HasDrawId(i, indexDraw))
            SessionGroup_RemoveDraw(i, indexDraw, execute_query);
}

stock SessionGroup_CloneAll(playerid, indexGroup, bool:choose = false) {

    new 
        index,
        Iterator:tempGroups<MAX_TEXTDRAWS_STUDIO> 
    ;

    if(choose)
        SessionPlayer_ResetLocalGroup(playerid);

    foreach(new i: SessionGroupsDraws[indexGroup]) {
        index = SessionTextDrawData_Copy(i);

        if(choose) 
            Iter_Add(tempGroups, index);

    }

    if(choose) {
        foreach(new i: tempGroups)
            SessionPlayer_AddDraw(playerid, i);
    }
}

stock SessionGroup_DestroyAll() {

    foreach(new i: SessionGroups)
        SessionGroup_Destroy(i, false);
}

stock bool:SessionGroup_HasDrawId(indexGroup, indexDraw)
    return Iter_Contains(SessionGroupsDraws[indexGroup], indexDraw);

stock SessionGroup_GetUniqueId(index)
    return e_SessionGroup[index][E_SESSIONGROUP_UNIQUE_ID];

stock SessionGroup_GetString(index, dest[], maxLength = sizeof dest)
    strcat(dest, e_SessionGroup[index][E_SESSIONGROUP_NAME], maxLength);

static stock SessionGroup_GetGenId(uniqueId) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT  \
                                                            id \
                                                        FROM groups \
                                                        WHERE project_id = %i \
                                                        ORDER BY id DESC \
                                                        LIMIT 1",
                                                        
                                                        uniqueId
                                                    );

    if(cache)
        return DB_GetFieldIntByName(cache, "id");

    return -1;
}

stock SessionGroup_GetIdByName(projectId, const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM groups WHERE project_id = %i AND name = '%s' LIMIT 1", projectId, name);
    if(cache) {
        if(DB_GetRowCount(cache)) {
            new uniqueId = DB_GetFieldIntByName(cache, "id");
            return uniqueId;
        }
        DB_FreeResultSet(cache);
    }
    return -1;
}

stock bool:SessionGroup_Exists(projectId, const name[])
    return SessionGroup_GetIdByName(projectId, name) != -1;
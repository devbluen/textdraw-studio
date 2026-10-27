
            // Definers
#define TRASH_TEXTDRAW_COLUMNS  "project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_rotation, model_colors, box, variable, invert"



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'

*/

stock SessionTrash_Count() {

    if(!Session_Has())
        return 0;

    new count = 0;
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT COUNT(*) AS count FROM trash WHERE project_id = %i", Session_GetId());

    if(cache)
    {
        count = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);
    }

    return count;
}

stock bool:SessionTrash_Restore(playerid, trashId) {

    if(!Session_Has())
        return false;

    new projectId = Session_GetId();

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM trash WHERE id = %i AND project_id = %i LIMIT 1", trashId, projectId);
    if(!cache)
        return false;

    new exists = DB_GetRowCount(cache);
    DB_FreeResultSet(cache);

    if(!exists)
        return false;

    // The restored textdraw is placed in the first free slot, exactly like a brand new one
    new index = Iter_Free(SessionDraws);
    if(index == ITER_NONE)
    {
        SendLang(playerid, -1, E_LANG_TRASH_FULL);
        return false;
    }

    Undo_Touch();

    cache = DB_ExecuteQuery(
        IDConnection,
        "INSERT INTO textdraws ("#TRASH_TEXTDRAW_COLUMNS") \
         SELECT project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, %i, itemType, model, model_rotation, model_colors, box, variable, invert \
         FROM trash \
         WHERE id = %i AND project_id = %i",

            index,
            trashId,
            projectId
    );

    if(!cache)
        return false;

    DB_FreeResultSet(cache);

    DB_FreeResultSet(
        DB_ExecuteQuery(IDConnection, "DELETE FROM trash WHERE id = %i", trashId)
    );

    new uniqueId = SessionTextDrawData_GetGenId(projectId);
    if(uniqueId != -1)
        SessionTextDrawData_Load(index, uniqueId);

    SessionTextDraw_UpdateButtonAll();

    SendLang(playerid, -1, E_LANG_TRASH_RESTORED);
    return true;
}

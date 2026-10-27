
            // Definers
#define UNDO_TEXTDRAW_COLUMNS   "id, project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_rotation, model_colors, box, variable, invert"
#define UNDO_TRASH_COLUMNS      "project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_rotation, model_colors, box, variable, invert"

static
    gUndoCount,
    gUndoDepth,
    bool:gUndoBatchSnapped,
    bool:gUndoLock
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

stock Undo_Init()
{
    gUndoLock = false;
    gUndoDepth = 0;
    gUndoBatchSnapped = false;
    gUndoCount = 0;

    if(!Session_Has())
        return;

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT COUNT(*) AS count FROM undo_steps WHERE project_id = %i", Session_GetId());

    if(cache)
    {
        gUndoCount = DB_GetFieldIntByName(cache, "count");
        DB_FreeResultSet(cache);
    }
}

stock Undo_Reset()
{
    gUndoLock = false;
    gUndoDepth = 0;
    gUndoBatchSnapped = false;
    gUndoCount = 0;
}

stock Undo_Count()
    return gUndoCount;

stock bool:Undo_Has()
    return gUndoCount > 0;

stock Undo_Begin()
{
    if(gUndoLock) return;

    if(gUndoDepth == 0)
        gUndoBatchSnapped = false;

    gUndoDepth++;
}

stock Undo_End()
{
    if(gUndoLock) return;

    if(gUndoDepth > 0)
        gUndoDepth--;

    if(gUndoDepth == 0)
        gUndoBatchSnapped = false;
}

stock Undo_Touch()
{
    if(gUndoLock)
        return;

    if(gUndoDepth > 0)
    {
        if(gUndoBatchSnapped)
            return;

        gUndoBatchSnapped = true;
    }

    Undo_Snapshot();
}

stock bool:Undo_Perform(playerid)
{
    if(!Session_Has())
        return false;

    if(gUndoCount <= 0)
    {
        SendLang(playerid, -1, E_LANG_UNDO_EMPTY);
        return false;
    }

    new projectId = Session_GetId();
    new step = Undo_GetLastStep(projectId);

    if(step <= 0)
    {
        Undo_Init();
        SendLang(playerid, -1, E_LANG_UNDO_EMPTY);
        return false;
    }

    gUndoLock = true;
    Undo_RestoreStep(step);

    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "DELETE FROM undo_steps WHERE id = %i", step));

    gUndoCount--;
    if(gUndoCount < 0) gUndoCount = 0;

    Session_ReloadAll();
    gUndoLock = false;

    SendLang(playerid, -1, E_LANG_UNDO_DONE);
    return true;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b
                    888   .d88'  888       8   888     888  888          888  888
                    888ooo88P'   888       8   888oooo888'  888          888  888
                    888          888       8   888    `88b  888          888  888
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'

*/

static stock Undo_GetLastStep(projectId)
{
    new step = 0;
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM undo_steps WHERE project_id = %i ORDER BY id DESC LIMIT 1", projectId);

    if(cache)
    {
        if(DB_GetRowCount(cache))
            step = DB_GetFieldIntByName(cache, "id");

        DB_FreeResultSet(cache);
    }

    return step;
}

static stock Undo_Snapshot()
{
    if(gUndoLock || !Session_Has())
        return 0;

    new projectId = Session_GetId();

    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "INSERT INTO undo_steps (project_id) VALUES (%i)", projectId));

    new step = Undo_GetLastStep(projectId);
    if(step <= 0)
        return 0;

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO undo_textdraws (step_id, "#UNDO_TEXTDRAW_COLUMNS") \
             SELECT %i, "#UNDO_TEXTDRAW_COLUMNS" \
             FROM textdraws \
             WHERE project_id = %i",

            step,
            projectId
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO undo_groups (step_id, id, project_id, name, indexGroup) \
             SELECT %i, id, project_id, name, indexGroup \
             FROM groups \
             WHERE project_id = %i",

            step,
            projectId
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO undo_groups_textdraws (step_id, draw_id, group_id) \
             SELECT %i, gt.draw_id, gt.group_id \
             FROM groups_textdraws gt \
             JOIN textdraws t ON t.id = gt.draw_id \
             WHERE t.project_id = %i",

            step,
            projectId
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO undo_trash (step_id, "#UNDO_TRASH_COLUMNS") \
             SELECT %i, "#UNDO_TRASH_COLUMNS" \
             FROM trash \
             WHERE project_id = %i",

            step,
            projectId
        )
    );

    gUndoCount++;

    foreach(new i: Users)
        TaskBarEventUpdate_Buttons(i);

    return step;
}

static stock Undo_RestoreStep(step)
{
    new projectId = Session_GetId();

    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "BEGIN TRANSACTION"));

    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "DELETE FROM textdraws WHERE project_id = %i", projectId));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "DELETE FROM groups WHERE project_id = %i", projectId));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "DELETE FROM trash WHERE project_id = %i", projectId));

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO textdraws ("#UNDO_TRASH_COLUMNS") \
             SELECT "#UNDO_TRASH_COLUMNS" \
             FROM undo_textdraws \
             WHERE step_id = %i",

            step
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO groups (project_id, name, indexGroup) \
             SELECT project_id, name, indexGroup \
             FROM undo_groups \
             WHERE step_id = %i",

            step
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO groups_textdraws (draw_id, group_id) \
             SELECT nt.id, ng.id \
             FROM undo_groups_textdraws ugt \
             JOIN undo_textdraws ut ON ut.step_id = ugt.step_id AND ut.id = ugt.draw_id \
             JOIN undo_groups ug ON ug.step_id = ugt.step_id AND ug.id = ugt.group_id \
             JOIN textdraws nt ON nt.project_id = %i AND nt.indexDraw = ut.indexDraw \
             JOIN groups ng ON ng.project_id = %i AND ng.indexGroup = ug.indexGroup \
             WHERE ugt.step_id = %i",

            projectId,
            projectId,
            step
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO trash ("#UNDO_TRASH_COLUMNS") \
             SELECT "#UNDO_TRASH_COLUMNS" \
             FROM undo_trash \
             WHERE step_id = %i",

            step
        )
    );

    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "COMMIT"));
}



static
    e_CopyProject[MAX_PLAYERS]
;

stock TaskBarEventProjectCopy_Show(playerid, uniqueId) {

    new name[30 + 1];
    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT name FROM projects WHERE id = %i LIMIT 1", uniqueId);

    if(!cache || !DB_GetRowCount(cache)) {

        if(cache) DB_FreeResultSet(cache);

        TaskBarEventProjectList_SamePage(playerid);
        return;
    }

    DB_GetFieldStringByName(cache, "name", name);
    DB_FreeResultSet(cache);

    e_CopyProject[playerid] = uniqueId;

    new dialog[156 + 1];
    LangF(playerid, dialog, sizeof dialog, E_LANG_PRJ_COPY_BODY, name);

    Dialog_Show(playerid, D_TASKBAR_PROJECTCOPY, DIALOG_STYLE_INPUT, L(playerid, E_LANG_PRJ_COPY), dialog, L(playerid, E_LANG_COPY), L(playerid, E_LANG_BTN_PREVIOUS));
}

static stock bool:TaskBarEventProjectCopy_Exists(const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM projects WHERE name = '%s' LIMIT 1", name);

    if(cache) {
        new count = DB_GetRowCount(cache);
        DB_FreeResultSet(cache);
        return count > 0;
    }

    return false;
}

static stock TaskBarEventProjectCopy_GetCopyId(const name[]) {

    new DBResult:cache = DB_ExecuteQuery(IDConnection, "SELECT id FROM projects WHERE name = '%s' ORDER BY id DESC LIMIT 1", name);

    if(cache) {
        new uniqueId = DB_GetFieldIntByName(cache, "id");
        DB_FreeResultSet(cache);
        return uniqueId;
    }

    return 0;
}

static stock TaskBarEventProjectCopy_Create(uniqueId, const name[]) {

    new copyId;
    new date[34 + 1];

    Util_ConvertTimestamp(gettime(), date, 0);

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO projects (name, `date`, globalVariable, playerVariable) SELECT '%s', '%s', globalVariable, playerVariable FROM projects WHERE id = %i",

                name,
                date,
                uniqueId
        )
    );

    copyId = TaskBarEventProjectCopy_GetCopyId(name);
    if(!copyId)
        return 0;

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO textdraws (project_id, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_rotation, model_colors, box, variable) SELECT %i, position, size, letter_size, `text`, font, align, proportion, outline, shadow, color, colorBackground, colorBox, selectable, mode, indexDraw, itemType, model, model_rotation, model_colors, box, variable FROM textdraws WHERE project_id = %i ORDER BY indexDraw ASC",

                copyId,
                uniqueId
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO groups (project_id, name, indexGroup) SELECT %i, name, indexGroup FROM groups WHERE project_id = %i ORDER BY indexGroup ASC",

                copyId,
                uniqueId
        )
    );

    DB_FreeResultSet(
        DB_ExecuteQuery(
            IDConnection,
            "INSERT INTO groups_textdraws (draw_id, group_id) SELECT nt.id, ng.id FROM groups_textdraws gt JOIN textdraws ot ON ot.id = gt.draw_id JOIN groups og ON og.id = gt.group_id JOIN textdraws nt ON nt.project_id = %i AND nt.indexDraw = ot.indexDraw JOIN groups ng ON ng.project_id = %i AND ng.indexGroup = og.indexGroup WHERE ot.project_id = %i",

                copyId,
                copyId,
                uniqueId
        )
    );

    return copyId;
}

Dialog:D_TASKBAR_PROJECTCOPY(playerid, response, listitem, inputtext[]) {

    if(response) {

        if(isnull(inputtext))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_EMPTY));

        if(strlen(inputtext) > 30)
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_NAME_TOO_LARGE));

        if(TaskBarEventProjectCopy_Exists(inputtext))
            return Dialog_ReShow(playerid, L(playerid, E_LANG_ERR_PROJECT_EXISTS));

        if(TaskBarEventProjectCopy_Create(e_CopyProject[playerid], inputtext))
            SendLang(INVALID_PLAYER_ID, -1, E_LANG_MSG_PRJ_COPIED, inputtext);

        TaskBarEventProjectList_SamePage(playerid);
        return true;
    }

    TaskBarEventProjectList_Options(playerid, e_CopyProject[playerid]);
    return true;
}


#include <YSI_Coding\y_hooks>

#define eTableProjects \
    "CREATE TABLE IF NOT EXISTS projects ( \
        id INTEGER, \
        name TEXT NOT NULL, \
        date TEXT NOT NULL, \
        PRIMARY KEY(id) \
    )"

#define eTableTextdraws \
    "CREATE TABLE IF NOT EXISTS textdraws ( \
        id INTEGER, \
        project_id INTEGER, \
        position TEXT DEFAULT '0.0,0.0', \
        size TEXT DEFAULT '0.0,0.0', \
        letter_size TEXT DEFAULT '0.0,0.0', \
        text TEXT, \
        font INTEGER, \
        align INTEGER, \
        proportion INTEGER, \
        outline INTEGER, \
        shadow INTEGER, \
        color INTEGER, \
        colorBackground INTEGER, \
        colorBox INTEGER, \
        selectable INTEGER, \
        mode INTEGER, \
        indexDraw INTEGER, \
        itemType INTEGER, \
        model INTEGER DEFAULT 1, \
        model_rotation TEXT DEFAULT '0.0,0.0,0.0,1.0', \
        model_colors TEXT DEFAULT '0,0', \
        box INTEGER DEFAULT 0, \
        PRIMARY KEY(id), \
        CONSTRAINT textdraws_project_id_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableGroups \
    "CREATE TABLE groups ( \
        id INTEGER, \
        project_id INTEGER, \
        name TEXT, \
        indexGroup INTEGER, \
        PRIMARY KEY(id), \
        CONSTRAINT project_id_groups_projects_id FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

#define eTableGroupsTextDraws \
    "CREATE TABLE groups_textdraws ( \
        draw_id	INTEGER, \
        group_id INTEGER, \
        CONSTRAINT groups_textdraws_id_textdraws_id FOREIGN KEY(draw_id) REFERENCES textdraws(id) ON DELETE CASCADE ON UPDATE CASCADE, \
        CONSTRAINT groups_id_textdraws_id FOREIGN KEY(group_id) REFERENCES groups(id) ON DELETE CASCADE ON UPDATE CASCADE \
    )"

hook OnGameModeInit() {

    IDConnection = DB_Open("textdrawStudio.db");

    if(IDConnection) Logger("Connection established successfully");
    else
    {
        Logger("Connection to database.db failed. Create this file in scriptfiles.");
        SendRconCommand("exit");
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // Prepare Tables
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, "PRAGMA foreign_keys = ON;"));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableProjects));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableTextdraws));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableGroups));
    DB_FreeResultSet(DB_ExecuteQuery(IDConnection, eTableGroupsTextDraws));
    return Y_HOOKS_CONTINUE_RETURN_1;
}